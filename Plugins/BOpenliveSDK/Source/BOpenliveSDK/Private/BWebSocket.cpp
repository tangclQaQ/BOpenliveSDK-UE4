#include "BWebsocket.h"
#include "iostream"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"

/*
 * �Խ�BվWebSocket
 */
UBWebsocket::UBWebsocket(){
}

UBWebsocket::~UBWebsocket()
{
}

void UBWebsocket::init(const ApiInfo& apiInfo, CALLBACKERROR CallbackError, CALLBACKMESSAGE CallbackMessage)
{
	m_apiInfo = apiInfo;
	if (apiInfo.wssLink.empty()) {
		CallbackError(ERROR_DATA_INVAILD);
		return;
	}
	const FString ServerURL = apiInfo.wssLink[0].c_str(); // Ĭ��ʹ�õ�һ��url
	const FString ServerProtocol = TEXT("ws");              // The WebServer protocol you want to use.
	Socket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);

	// We bind all available events
	Socket->OnConnected().AddLambda([&]() -> void {
		// This code will run once connected.
		std::stringstream ss;
		//unsigned char buffer[4] = {};
		TArray<unsigned char> buffer;
		buffer.Init(0, 4);

		//д����֤�ַ�������
		getBytesByInt(buffer, (int)(m_apiInfo.authBody.length() + 16));

		ss << buffer[0] << buffer[1] << buffer[2] << buffer[3];
		// 16�Ǳ���ģ���Ȼ��֪��Ϊʲô
		getBytesByShort(buffer, (short)16);
		ss << buffer[0] << buffer[1];

		//���ڹ�˵�Ѿ��� protover = 3 ��, ��֮��protover 2�õ���Ϊֹ
		getBytesByShort(buffer, (short)2);
		ss << buffer[0] << buffer[1];

		// 7�Ǽ��뷿��Ļ�ȡ��Ļ(Ҳ���Ǽ�Ȩ��)��2����������ֹǿ�Ƶ���
		getBytesByInt(buffer, (int)7);
		ss << buffer[0] << buffer[1] << buffer[2] << buffer[3];


		
		getBytesByInt(buffer, (int)1);
		ss << buffer[0] << buffer[1] << buffer[2] << buffer[3];

		//���json�ַ���Ҳд���ȥ
		ss << m_apiInfo.authBody;
		//������ɷ���������������͸�������
		std::string roomPack = ss.str();
		FString rooPackStr(roomPack.c_str());

		// �˴���'\0'���ܰ�����ȥ
		if (!Socket->IsConnected())
		{
			// Don't send if we're not connected.
			UE_LOG(LogTemp, Log, TEXT("WebSocket is not connected"));
			CallbackError(ERROR_WEBSOCKET_CONNECT);
			return;
		}
		Socket->Send(roomPack.data(), roomPack.size(), true);
		UWorld* world = GEngine->GameViewport->GetWorld();
		if (world == nullptr) {
			UE_LOG(LogTemp, Log, TEXT("UWorld is null"));
			return;
		}
		world->GetTimerManager().SetTimer(m_beatTimer, this, &UBWebsocket::heartBeat, 29, true);
		});

		Socket->OnConnectionError().AddLambda([=](const FString& Error) -> void {
			// This code will run if the connection failed. Check Error to see what happened.
			UE_LOG(LogTemp, Log, TEXT("WebSocket err is :&s"), *Error);
			CallbackError(ERROR_WEBSOCKET_CONNECT);
			});

		Socket->OnClosed().AddLambda([=](int32 StatusCode, const FString& Reason, bool bWasClean) -> void {
			// This code will run when the connection to the server has been terminated.
			// Because of an error or a call to Socket->Close().
			// �Ͽ������ˣ���ô�͹ر�websocket�������������Ѿ��Ͽ����ź�,�ر�������ʱ��
			UE_LOG(LogTemp, Log, TEXT("WebSocket is closed, Reason is %s"), *Reason);
			this->Socket->Close();
			CallbackError(ERROR_WEBSOCKET_DISCONNECT);
			UWorld* WorldPtr = GEngine->GameViewport->GetWorld();
			if(WorldPtr != nullptr)
			{
				GetWorld()->GetTimerManager().ClearTimer(m_beatTimer);
			}
			});

		Socket->OnRawMessage().AddLambda([=](const void* Message/* Data */, SIZE_T Size/* Size */, SIZE_T BytesRemaining) -> void {
			// This code will run when we receive a string message from the server.
			//���ӳɹ�������26���ֽڵ�����,����ֱ��ʡ���ⲽ�Ľ���
    		if (Size != 26)
    		{
    		    unsigned char *buffer = (unsigned char *)Message;
    		    //��ȡ���ĳ���
    		    int packetLength = toInt(buffer, 0);
		
    		    int headerLength = toShort(buffer, 4);
    		    //��������,2Ϊgzip���ݰ�����Ļ���������ֱ����Ķ�����������
    		    int version = toShort(buffer, 6);
    		    int action = toInt(buffer, 8);
    		    int parameter = toInt(buffer, 12);
		
    		    if (packetLength > 20)
    		    {
    		        // version == 2 ��ʾ����ʹ����zlibѹ��
    		        if (version == 2)
    		        {
    		            uLong unzip_size = UNZIP_BUFF_SIZE;
    		            if (uncompress(unzipBuffer, &unzip_size, buffer + 16, packetLength - 16) == 0)
    		            {
    		                //�˴�����ѹ�������������ݱ���֮Ϊ����������ÿ����Ļ��Ϣ����Ϊ�Ӱ�
    		                //��ʱ���Ƕ���Ӱ�����һ���͹����ģ�Ҫ�����������ʴ�������ʼλ�ÿ϶���0��ʼ��
    		                uLong allsize = 0;
    		                //��Ҫ����λ�ø���ѹ�����Ĵ�Сһ��ʱ���Ǿ��������������������
    		                while (allsize < unzip_size)
    		                {
    		                    //��ȡ�Ӱ��ĳ��ȣ�����¼
    		                    int packetLength2 = toInt(unzipBuffer, allsize + 0);
    		                    int headerLength2 = toShort(unzipBuffer, allsize + 4);
    		                    int version2 = toShort(unzipBuffer, allsize + 6);
    		                    int action2 = toInt(unzipBuffer, allsize + 8);
    		                    int parameter2 = toInt(unzipBuffer, allsize + 12);
		
    		                    //��ȡ�ַ���
    		                    int end = packetLength2 + allsize;
    		                    char c = unzipBuffer[end];
    		                    unzipBuffer[end] = '\0';
    		                    std::string data = (char *)(unzipBuffer + allsize + 16);
    		                    unzipBuffer[end] = c;
		
    		                    // Ȼ����Ǵ��������� ...
    		                	CallbackMessage(data);
		
    		                    //����������Ӱ���ǵý��������λ�ý���ƫ��
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

void UBWebsocket::getBytesByInt(TArray<unsigned char> &buffer, int value)
{
	buffer[0] = (unsigned char)(value >> 24);
	buffer[1] = (unsigned char)(value >> 16);
	buffer[2] = (unsigned char)(value >> 8);
	buffer[3] = (unsigned char)value;
}

void UBWebsocket::getBytesByShort(TArray<unsigned char> &buffer, short value)
{
	buffer[0] = (unsigned char)(value >> 8);
	buffer[1] = (unsigned char)value;
}

int UBWebsocket::toInt(unsigned char* buffer, int index)
{
	return (((int)buffer[index] << 24) | ((int)buffer[index + 1] << 16) | ((int)buffer[index + 2] << 8) | (int)buffer[index + 3]);
}

int UBWebsocket::toShort(unsigned char* buffer, int index)
{
	return ((int)buffer[index] << 8) | (int)buffer[index + 1];
}

void UBWebsocket::heartBeat()
{
	//������
	static char heartBeatData[16] = { 0x00, 0x00, 0x00, 0x10,
								  0x00, 0x10,
								  0x00, 0x01,
								  0x00, 0x00, 0x00, 0x02,
								  0x00, 0x00, 0x00, 0x01 };

	// ֻ��websocket��������������״̬�²��ܷ���������
	if (this->Socket != nullptr && this->Socket->IsConnected())
	{
		this->Socket->Send(heartBeatData, sizeof(heartBeatData), true);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("websocket�쳣"));
	}
}

bool UBWebsocket::getIsConnected()
{
	return Socket->IsConnected();
}