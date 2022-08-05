// Copyright 2022 斑_tcl, Inc. All Rights Reserved.

#include "BOpenliveSDKBPLibrary.h"
#include "BOpenliveSDK.h"
#include "Engine.h"

UBOpenliveSDKBPLibrary*	UBOpenliveSDKBPLibrary::s_UBSdk = nullptr;
UBOpenliveSDKBPLibrary::UBOpenliveSDKBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UBOpenliveSDKBPLibrary* UBOpenliveSDKBPLibrary::GetInstancePtr()
{
	if (s_UBSdk == nullptr)
	{
		s_UBSdk = NewObject<UBOpenliveSDKBPLibrary>();
		s_UBSdk->AddToRoot();
	}
	return s_UBSdk;
}

void UBOpenliveSDKBPLibrary::init(FString accessKeyId, FString accessKeySecret, FString appId, FString code)
{
	m_accessKeyId = TCHAR_TO_UTF8(*accessKeyId);
	m_accessKeySecret = TCHAR_TO_UTF8(*accessKeySecret);
	m_appId = TCHAR_TO_UTF8(*appId);
	m_code = TCHAR_TO_UTF8(*code);
	bapi = new BApi(m_accessKeyId, m_accessKeySecret);
}

void UBOpenliveSDKBPLibrary::CreateWebsocket()
{
	if (danMuQWebsocket == nullptr) {
		danMuQWebsocket = NewObject<UBWebsocket>(this);
		danMuQWebsocket->AddToRoot();
	}
	danMuQWebsocket->init(apiInfo, WebSocketError, WebSocketMessage);
}

void UBOpenliveSDKBPLibrary::WebSocketError(EErrorString error)
{

}

void UBOpenliveSDKBPLibrary::WebSocketMessage(std::string message)
{
	try
	{
		nlohmann::json jsonData = nlohmann::json::parse(message);
		std::string cmd = jsonData["cmd"].get<std::string>();
		if (cmd.find("LIVE_OPEN_PLATFORM_DM") != std::string::npos) {
			GetInstancePtr()->danmuData.setValue(jsonData["data"]);
			GetInstancePtr()->ReceiveDanmuEvent.Broadcast(GetInstancePtr()->danmuData);
		} else if (cmd.find("LIVE_OPEN_PLATFORM_SEND_GIFT") != std::string::npos) {
			GetInstancePtr()->giftData.setValue(jsonData["data"]);
			GetInstancePtr()->FReceiveGiftEvent.Broadcast(GetInstancePtr()->giftData);
		} else if (cmd.find("LIVE_OPEN_PLATFORM_SUPER_CHAT") != std::string::npos) {
			GetInstancePtr()->superChatData.setValue(jsonData["data"]);
			GetInstancePtr()->FReceiveSuperChatDataEvent.Broadcast(GetInstancePtr()->superChatData);
		} else if (cmd.find("LIVE_OPEN_PLATFORM_SUPER_CHAT_DEL") != std::string::npos) {
			GetInstancePtr()->superChatDelData.setValue(jsonData["data"]);
			//好像没什么用，暂时不发事件
		} else if (cmd.find("LIVE_OPEN_PLATFORM_GUARD") != std::string::npos) {
			GetInstancePtr()->guardBuyData.setValue(jsonData["data"]);
			GetInstancePtr()->FReceiveGuardBuyEvent.Broadcast(GetInstancePtr()->guardBuyData);
		}
	}
	catch (nlohmann::detail::exception& e)
	{
		UE_LOG(LogTemp, Log, TEXT("json数据异常，错误码：%d"), e.id);
	}
}

void UBOpenliveSDKBPLibrary::Start()
{
	bapi->StartInteractivePlay(m_code, m_appId, OnStartInteractivePlay);
}

void UBOpenliveSDKBPLibrary::Stop()
{
	if(GEngine != nullptr && GEngine->GameViewport != nullptr) {
		UWorld* world = GEngine->GameViewport->GetWorld();
		if(world != nullptr)
		{
			world->GetTimerManager().ClearTimer(m_beatTimer);
		}
	}
	bapi->EndInteractivePlay(m_appId, apiInfo.gameId, OnEndInteractivePlay);
}

void UBOpenliveSDKBPLibrary::OnEndInteractivePlay(bool isSuccess, const std::string& message)
{
	if(isSuccess == false)
	{
		//TODO:notify error
		return;
	}
	FString messageStr(UTF8_TO_TCHAR(message.c_str()));
	UE_LOG(LogTemp, Log, TEXT("message is %s"), *messageStr);
	try
	{
		nlohmann::json jsonData = nlohmann::json::parse(message);
		if (jsonData.find("code") != jsonData.end()) {
			if (jsonData["code"].get<int64_t>() == 0) {
				UE_LOG(LogTemp, Log, TEXT("请求结束成功"));
			} else {
				UE_LOG(LogTemp, Log, TEXT("请求结束失败"));
			}
		} else {
			UE_LOG(LogTemp, Log, TEXT("请求错误"));
		}
	}
	catch (nlohmann::detail::exception& e)
	{
		UE_LOG(LogTemp, Log, TEXT("json数据异常，错误码：%d"), e.id);
	}
}

void UBOpenliveSDKBPLibrary::OnStartInteractivePlay(bool isSuccess, const std::string &message)
{
	if(isSuccess == false)
	{
		GetInstancePtr()->FStartErrorEvent.Broadcast(1, "网络异常");
		return;
	}
	try
	{
		nlohmann::json jsonData = nlohmann::json::parse(message);
		assert(jsonData["code"].get<int64_t>() == 0);
		FString messageStr(UTF8_TO_TCHAR(message.c_str()));
		UE_LOG(LogTemp, Log, TEXT("message is %s"), *messageStr);
		int64_t code = jsonData["code"].get<int64_t>();
		FString msg(UTF8_TO_TCHAR(jsonData["message"].get<std::string>().c_str()));
		if (code != 0) {
			GetInstancePtr()->FStartErrorEvent.Broadcast(code, msg);
			return;
		}
		UWorld* world = GEngine->GameViewport->GetWorld();
		if (world == nullptr) {
			UE_LOG(LogTemp, Log, TEXT("UWorld is null"));
		}
		world->GetTimerManager().SetTimer(GetInstancePtr()->m_beatTimer, GetInstancePtr(), &UBOpenliveSDKBPLibrary::timerEvent, 1, true); // 掉线检测和发送心跳包
		GetInstancePtr()->apiInfo.setValue(jsonData["data"]);
		GetInstancePtr()->CreateWebsocket();
	}
	catch (nlohmann::detail::exception& e)
	{
		GetInstancePtr()->FStartErrorEvent.Broadcast(2, "json数据异常");
		UE_LOG(LogTemp, Log, TEXT("json数据异常，错误码：%d"), e.id);
	}
}

void UBOpenliveSDKBPLibrary::timerEvent()
{
	static int count = 0;
	// 这里使用的是19秒发一次心跳包
	if (count >= 19) {
		bapi->HeartBeatInteractivePlay(apiInfo.gameId, &UBOpenliveSDKBPLibrary::OnTimerEvent);
		count = 0;
	} else {
		++count;
	}
	// 每秒都会判断websocket是否断开了，断开的话就重连
	if (!danMuQWebsocket->getIsConnected()) {
		UE_LOG(LogTemp, Log, TEXT("websocket re connect"));
		CreateWebsocket();
	}
}

void UBOpenliveSDKBPLibrary::OnTimerEvent(bool isSuccess, const std::string & response)
{
	if(isSuccess)
	{
		try
		{
			nlohmann::json jsonData = nlohmann::json::parse(response);
			if (jsonData.find("code") != jsonData.end()) {
				if (jsonData["code"].get<int64_t>() == 0) {
					UE_LOG(LogTemp, Log, TEXT("发送心跳包响应成功。"));
				} else {
					UE_LOG(LogTemp, Log, TEXT("发送心跳包响应失败，有可能是超时了"));
				}
			} else {
				UE_LOG(LogTemp, Log, TEXT("发送心跳包失败1。"));
			}
		}
		catch (nlohmann::detail::exception& e)
		{
			UE_LOG(LogTemp, Log, TEXT("json数据异常，错误码：%d"), e.id);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("发送心跳包失败2。"));
	}
}