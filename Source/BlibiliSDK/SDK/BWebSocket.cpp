#include "BWebsocket.h"

/*
 * 对接B站WebSocket
 */
UBWebsocket::UBWebsocket(){
}

UBWebsocket::~UBWebsocket()
{
	Socket->Close();
}

void UBWebsocket::init(const ApiInfo& apiInfo, CALLBACKERROR CallbackError, CALLBACKMESSAGE CallbackMessage)
{
	m_apiInfo = apiInfo;
	if (apiInfo.wssLink.empty()) {
		CallbackError(ERROR_DATA_INVAILD);
		return;
	}
	const FString ServerURL = apiInfo.wssLink[0].c_str(); // 默认使用第一条url
	const FString ServerProtocol = TEXT("ws");              // The WebServer protocol you want to use.
	Socket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);

	// We bind all available events
	Socket->OnConnected().AddLambda([=]() -> void {
		// This code will run once connected.
		std::stringstream ss;
		danmakuByte buffer[4];

		//写入验证字符串长度
		getBytesByInt(buffer, (int)(m_apiInfo.authBody.length() + 16));

		ss << buffer[0] << buffer[1] << buffer[2] << buffer[3];
		// 16是必须的，虽然不知道为什么
		getBytesByShort(buffer, (short)16);
		ss << buffer[0] << buffer[1];

		//有内鬼说已经有 protover = 3 了, 总之把protover 2用到死为止
		getBytesByShort(buffer, (short)2);
		ss << buffer[0] << buffer[1];

		// 7是加入房间的获取弹幕(也就是鉴权包)，2是心跳包防止强制掉线
		getBytesByInt(buffer, (int)7);
		ss << buffer[0] << buffer[1] << buffer[2] << buffer[3];


		
		getBytesByInt(buffer, (int)1);
		ss << buffer[0] << buffer[1] << buffer[2] << buffer[3];

		//最后将json字符串也写入进去
		ss << m_apiInfo.authBody;
		//最后生成房间包，并将包发送给服务器
		std::string roomPack = ss.str();

		// 此处的'\0'不能包括进去
		if (!Socket->IsConnected())
		{
			// Don't send if we're not connected.
			CallbackError(ERROR_WEBSOCKET_CONNECT);
			return;
		}
		Socket->Send(roomPack.c_str());

		GetWorld()->GetTimerManager().SetTimer(m_beatTimer, this, &UBWebsocket::heartBeat, 29, true);
		});

		Socket->OnConnectionError().AddLambda([=](const FString& Error) -> void {
			// This code will run if the connection failed. Check Error to see what happened.
			UE_LOG(LogTemp, Log, TEXT("WebSocket err is :&s"), *Error);
			CallbackError(ERROR_WEBSOCKET_CONNECT);
			});

		Socket->OnClosed().AddLambda([=](int32 StatusCode, const FString& Reason, bool bWasClean) -> void {
			// This code will run when the connection to the server has been terminated.
			// Because of an error or a call to Socket->Close().
			// 断开连接了，那么就关闭websocket，并发送连接已经断开的信号
			UE_LOG(LogTemp, Log, TEXT("WebSocket is closed"));
			this->Socket->Close();
			});

		Socket->OnMessage().AddLambda([=](const FString& Message) -> void {
			// This code will run when we receive a string message from the server.
			//连接成功，返回26个字节的数据,这里直接省略这步的解析
    		if (Message.Len() != 26)
    		{
    		    danmakuByte *buffer = (danmakuByte *)GetData(Message);
    		    //读取包的长度
    		    int packetLength = toInt(buffer, 0);
		
    		    int headerLength = toShort(buffer, 4);
    		    //处理类型,2为gzip数据包，弹幕，礼物，进入直播间的都是这种数据
    		    int version = toShort(buffer, 6);
    		    int action = toInt(buffer, 8);
    		    int parameter = toInt(buffer, 12);
		
    		    if (packetLength > 20)
    		    {
    		        // version == 2 表示数据使用了zlib压缩
    		        if (version == 2)
    		        {
    		            uLong unzip_size = UNZIP_BUFF_SIZE;
    		            if (uncompress(unzipBuffer, &unzip_size, buffer + 16, packetLength - 16) == 0)
    		            {
    		                //此处，解压出来的所有数据被称之为大包，里面的每条弹幕信息被称为子包
    		                //有时候是多个子包放在一起发送过来的，要对整个包解剖处理，初始位置肯定从0开始了
    		                uLong allsize = 0;
    		                //当要处理位置跟解压出来的大小一致时，那就是整个大包都处理完了
    		                while (allsize < unzip_size)
    		                {
    		                    //读取子包的长度，并记录
    		                    int packetLength2 = toInt(unzipBuffer, allsize + 0);
    		                    int headerLength2 = toShort(unzipBuffer, allsize + 4);
    		                    int version2 = toShort(unzipBuffer, allsize + 6);
    		                    int action2 = toInt(unzipBuffer, allsize + 8);
    		                    int parameter2 = toInt(unzipBuffer, allsize + 12);
		
    		                    //提取字符串
    		                    int end = packetLength2 + allsize;
    		                    char c = unzipBuffer[end];
    		                    unzipBuffer[end] = '\0';
    		                    std::string data = (char *)(unzipBuffer + allsize + 16);
    		                    unzipBuffer[end] = c;
		
    		                    // 然后就是处理数据了 ...
    		                	CallbackMessage(data);
		
    		                    //处理完这个子包后记得将大包处理位置进行偏移
    		                    allsize += packetLength2;
    		                }
    		            }
    		        }
    		        else
    		        {
    		            memcpy(unzipBuffer, buffer + 16, packetLength - 16);
    		            unzipBuffer[packetLength - 16] = '\0';
    		        	CallbackMessage((const char *)unzipBuffer);
    		        }
    		    }
    		}
			});

		Socket->OnRawMessage().AddLambda([](const void* Data, SIZE_T Size, SIZE_T BytesRemaining) -> void {
			// This code will run when we receive a raw (binary) message from the server.
			});

		Socket->OnMessageSent().AddLambda([](const FString& MessageString) -> void {
			// This code is called after we sent a message to the server.
			});

		// And we finally connect to the server. 
		Socket->Connect();
}

void UBWebsocket::getBytesByInt(danmakuByte* buffer, int value)
{
	buffer[0] = (danmakuByte)(value >> 24);
	buffer[1] = (danmakuByte)(value >> 16);
	buffer[2] = (danmakuByte)(value >> 8);
	buffer[3] = (danmakuByte)value;
}

void UBWebsocket::getBytesByShort(danmakuByte* buffer, short value)
{
	buffer[0] = (danmakuByte)(value >> 8);
	buffer[1] = (danmakuByte)value;
}

int UBWebsocket::toInt(danmakuByte* buffer, int index)
{
	return (((int)buffer[index] << 24) | ((int)buffer[index + 1] << 16) | ((int)buffer[index + 2] << 8) | (int)buffer[index + 3]);
}

int UBWebsocket::toShort(danmakuByte* buffer, int index)
{
	return ((int)buffer[index] << 8) | (int)buffer[index + 1];
}

void UBWebsocket::heartBeat()
{
	//心跳包
	static char heartBeat[16] = { 0x00, 0x00, 0x00, 0x10,
								  0x00, 0x10,
								  0x00, 0x01,
								  0x00, 0x00, 0x00, 0x02,
								  0x00, 0x00, 0x00, 0x01 };

	// 只有websocket还处于正常连接状态下才能发送心跳包
	if (this->Socket != nullptr && this->Socket->IsConnected())
	{
		this->Socket->Send(heartBeat);
	}
}
