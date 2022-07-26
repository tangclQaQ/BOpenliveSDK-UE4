#include "BSdk.h"

UBSdk*	UBSdk::s_UBSdk = nullptr;
UBSdk::~UBSdk()
{
	if (bapi != nullptr) {
        delete bapi;
        bapi = nullptr;
    }
}

UBSdk* UBSdk::GetInstancePtr()
{
	if (s_UBSdk == nullptr)
	{
		s_UBSdk = NewObject<UBSdk>();
		s_UBSdk->AddToRoot();
	}
	return s_UBSdk;
}

void UBSdk::init(const std::string& accessKeyId, const std::string& accessKeySecret, const std::string& appId,
                 const std::string& code)
{
	m_accessKeyId = accessKeyId;
	m_accessKeySecret = accessKeySecret;
	m_appId = appId;
	m_code = code;
	bapi = new BApi(accessKeyId, accessKeySecret);
}

void UBSdk::CreateWebsocket()
{
	if (danMuQWebsocket == nullptr) {
		danMuQWebsocket = NewObject<UBWebsocket>(this);
		danMuQWebsocket->AddToRoot();
	}
	danMuQWebsocket->init(apiInfo, WebSocketError, WebSocketMessage);
}

void UBSdk::WebSocketError(EErrorString error)
{

}

void UBSdk::WebSocketMessage(std::string message)
{
	nlohmann::json jsonData = nlohmann::json::parse(message);
	std::string cmd = jsonData["cmd"].get<std::string>();
	if (cmd.find("LIVE_OPEN_PLATFORM_DM") != std::string::npos) {
		GetInstancePtr()->danmaData.setValue(jsonData["data"]);
		FString uname = FString(UTF8_TO_TCHAR(jsonData["data"]["uname"].get<std::string>().c_str()));
		FString msg = FString(UTF8_TO_TCHAR(jsonData["data"]["msg"].get<std::string>().c_str()));
		UE_LOG(LogTemp, Log, TEXT("弹幕发送者：%s, 弹幕内容：%s"), *uname, *msg);
		//emit ReceivedDanmaKu(this->danmaData);
	} else if (cmd.find("LIVE_OPEN_PLATFORM_SEND_GIFT") != std::string::npos) {
		GetInstancePtr()->giftData.setValue(jsonData["data"]);
		//emit ReceivedGift(this->giftData);
	} else if (cmd.find("LIVE_OPEN_PLATFORM_SUPER_CHAT") != std::string::npos) {
		GetInstancePtr()->superChatData.setValue(jsonData["data"]);
		//emit ReceivedSuperChat(this->superChatData);
	} else if (cmd.find("LIVE_OPEN_PLATFORM_SUPER_CHAT_DEL") != std::string::npos) {
		GetInstancePtr()->superChatDelData.setValue(jsonData["data"]);
		//emit ReceivedSuperChatDel(this->superChatDelData);
	} else if (cmd.find("LIVE_OPEN_PLATFORM_GUARD") != std::string::npos) {
		GetInstancePtr()->guardBuyData.setValue(jsonData["data"]);
		//emit ReceivedGuardBuy(this->guardBuyData);
	}
}

void UBSdk::Start()
{
	bapi->StartInteractivePlay(m_code, m_appId, OnStartInteractivePlay);
}

void UBSdk::OnStartInteractivePlay(bool isSuccess, const std::string &message)
{
	if(isSuccess == false)
	{
		//TODO:notify error
		return;
	}
	nlohmann::json jsonData = nlohmann::json::parse(message);
	assert(jsonData["code"].get<int64_t>() == 0);
	FString messageStr(message.c_str());
	UE_LOG(LogTemp, Log, TEXT("message is %s"), *messageStr);
	int64_t code = jsonData["code"].get<int64_t>();
	if (code != 0) {
		//TODO:notify error
		return;
	}
	UWorld* world = GEngine->GameViewport->GetWorld();
	if (world == nullptr) {
		UE_LOG(LogTemp, Log, TEXT("UWorld is null"));
	}
	world->GetTimerManager().SetTimer(GetInstancePtr()->m_beatTimer, GetInstancePtr(), &UBSdk::timerEvent, 1, true); // 掉线检测和发送心跳包
	GetInstancePtr()->apiInfo.setValue(jsonData["data"]);
	GetInstancePtr()->CreateWebsocket();
}

void UBSdk::timerEvent()
{
	static int count = 0;
	// 这里使用的是19秒发一次心跳包
	if (count >= 19) {
		bapi->HeartBeatInteractivePlay(apiInfo.gameId, &UBSdk::OnTimerEvent);
		count = 0;
	} else {
		++count;
	}
	// 每秒都会判断websocket是否断开了，断开的话就重连
	if (danMuQWebsocket == nullptr) {
		UE_LOG(LogTemp, Log, TEXT("websocket re connect"));
		CreateWebsocket();
	}
}

void UBSdk::OnTimerEvent(bool isSuccess, const std::string & response)
{
	nlohmann::json jsonData = nlohmann::json::parse(response);
	if (jsonData.find("code") != jsonData.end()) {
		if (jsonData["code"].get<int64_t>() == 0) {
			UE_LOG(LogTemp, Log, TEXT("发送心跳包响应成功"));
		} else {
			UE_LOG(LogTemp, Log, TEXT("发送心跳包响应失败，有可能是超时了"));
			// 这样直接用我还没测试过，可能会有bug
			GetInstancePtr()->Start();
		}
	} else {
		UE_LOG(LogTemp, Log, TEXT("发送心跳包失败"));
	}
}

