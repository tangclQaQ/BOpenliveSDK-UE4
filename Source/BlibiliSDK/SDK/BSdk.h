#pragma once
#include "CoreMinimal.h"
#include "BApi.h"
#include "BApiInfo.h"
#include "BWebsocket.h"
#include "memory"



#include "BSdk.generated.h"

UCLASS()
class UBSdk : public UObject
{
	GENERATED_BODY()
public:
	~UBSdk();

	static UBSdk* GetInstancePtr();
	
	void init(const std::string &accessKeyId, const std::string &accessKeySecret, const std::string &appId, const std::string &code);
	void CreateWebsocket();
	static void WebSocketError(EErrorString error);
	static void WebSocketMessage(std::string string);

private:
	static UBSdk* s_UBSdk;
	std::string m_accessKeyId;     // 开发者id
	std::string m_accessKeySecret; // 开发者密钥
	std::string m_appId;           // 项目id
	std::string m_code;            // 主播身份码

	int timerId; // 计时器id

	ApiInfo apiInfo;

	DanmaData danmaData;               // 弹幕
	GiftData giftData;                 // 礼物
	GuardBuyData guardBuyData;         // 大航海
	SuperChatData superChatData;       // 付费留言
	SuperChatDelData superChatDelData; // 过时的付费留言id

	UBWebsocket *danMuQWebsocket = nullptr;
	BApi *bapi = nullptr;
};
