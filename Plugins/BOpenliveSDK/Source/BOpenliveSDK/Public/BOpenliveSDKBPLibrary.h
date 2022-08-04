// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BApi.h"
#include "BApiInfo.h"
#include "BWebsocket.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BOpenliveSDKBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceiveDanmu, FDanmuData, data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceiveGift, FGiftData, data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceiveSuperChatData, FSuperChatData, data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceiveGuardBuy, FGuardBuyData, data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartError, int32, errNo, FString, errString);

UCLASS()
class BOPENLIVESDK_API UBOpenliveSDKBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable)
	static UBOpenliveSDKBPLibrary* GetInstancePtr();
	UFUNCTION(BlueprintCallable)
	void init(FString accessKeyId, FString accessKeySecret, FString appId, FString code);
	UFUNCTION(BlueprintCallable)
	void Start();
	UFUNCTION(BlueprintCallable)
	void Stop();

public:
	void CreateWebsocket();
	static void WebSocketError(EErrorString error);
	static void WebSocketMessage(std::string message);
	static void OnEndInteractivePlay(bool isSuccess, const std::string& message);
	static void OnStartInteractivePlay(bool isSuccess, const std::string& message);
	void timerEvent();
	static void OnTimerEvent(bool isSuccess, const std::string & response);

	UPROPERTY(BlueprintAssignable)
	FReceiveDanmu ReceiveDanmuEvent;
	UPROPERTY(BlueprintAssignable)
	FReceiveGift FReceiveGiftEvent;
	UPROPERTY(BlueprintAssignable)
	FReceiveSuperChatData FReceiveSuperChatDataEvent;
	UPROPERTY(BlueprintAssignable)
	FReceiveGuardBuy FReceiveGuardBuyEvent;
	UPROPERTY(BlueprintAssignable)
	FStartError FStartErrorEvent;

private:
	static UBOpenliveSDKBPLibrary* s_UBSdk;
	std::string m_accessKeyId;     // 开发者id
	std::string m_accessKeySecret; // 开发者密钥
	std::string m_appId;           // 项目id
	std::string m_code;            // 主播身份码

	int timerId; // 计时器id

	ApiInfo apiInfo;

	FDanmuData danmuData;               // 弹幕
	FGiftData giftData;                 // 礼物
	FGuardBuyData guardBuyData;         // 大航海
	FSuperChatData superChatData;       // 付费留言
	SuperChatDelData superChatDelData; // 过时的付费留言id

	UBWebsocket *danMuQWebsocket = nullptr;
	BApi *bapi = nullptr;
	FTimerHandle m_beatTimer;
};
