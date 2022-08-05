#pragma once

// Copyright 2022 斑_tcl, Inc. All Rights Reserved.

#include <CoreMinimal.h>
#include <string>
#include <vector>
#include "BOpenliveSDK/Private/Tool/json.hpp"
#include <stdint.h>

#include "Engine/DataTable.h"

#include <BApiInfo.generated.h>

//认证所需的信息
struct AuthInfo
{
	std::string accessKeyId;
	std::string accessKeySecret;
	std::string appId;
	std::string code;
};

struct ApiInfo
{
	int64_t roomId;                   // 房间id
	int64_t uid;                      // 主播uid
	std::string uface;                // 主播头像
	std::string uname;                // 主播名称
	std::string gameId;               // 游戏id
	std::string authBody;             // 验证用的
	std::vector<std::string> wssLink; // wss可用的地址

	explicit ApiInfo(const nlohmann::json& jsonData);
	ApiInfo() = default;
	void setValue(const nlohmann::json& jsonData);
};

// 弹幕消息
USTRUCT(BlueprintType)
struct BOPENLIVESDK_API FDanmuData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 uid;                    // 用户UID
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 timestamp;              // 弹幕发送时间秒级时间戳
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 room_id;                // 弹幕接收的直播间
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 guard_level;            // 对应房间大航海等级
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 fans_medal_level;       // 对应房间勋章信息
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString msg_id;             // 消息唯一id
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	bool fans_medal_wearing_status; // 当前佩戴的粉丝勋章佩戴状态
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString uname;              // 用户昵称
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString uface;              // 用户头像
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString msg;                // 弹幕内容
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString fans_medal_name;    // 粉丝勋章名

	explicit FDanmuData(const nlohmann::json& jsonData);
	FDanmuData() = default;
	void setValue(const nlohmann::json& jsonData);
};

USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 uid;       // 收礼主播uid
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString uname; // 收礼主播昵称
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString uface; // 收礼主播头像

	FUserInfo() = default;
};

// 礼物
USTRUCT(BlueprintType)
struct FGiftData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 room_id;                // 房间号
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 uid;                    // 送礼用户UID
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 gift_id;                // 道具id(盲盒:爆出道具id)
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 gift_num;               // 赠送道具数量
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 price;                  // 支付金额(1000 = 1元 = 10电池),盲盒:爆出道具的价值
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 fans_medal_level;       // 实际送礼人的勋章信息
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 guard_level;            // 大航海等级
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 timestamp;              // 收礼时间秒级时间戳
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	bool paid;                      // 是否是付费道具
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	bool fans_medal_wearing_status; // 当前佩戴的粉丝勋章佩戴状态
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString uname;              //送礼用户昵称
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString uface;              // 送礼用户头像
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString gift_name;          // 道具名(盲盒:爆出道具名)
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString fans_medal_name;    //粉丝勋章名
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString msg_id;             // 消息唯一id
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FUserInfo anchor_info;           // 主播信息

	explicit FGiftData(const nlohmann::json& jsonData);
	FGiftData() = default;
	void setValue(const nlohmann::json& jsonData);
};

// 大航海
USTRUCT(BlueprintType)
struct FGuardBuyData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 guard_level;            // 大航海等级
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 guard_num;              // 大航海数量
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 fans_medal_level;       // 粉丝勋章等级
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 room_id;                // 房间号
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 timestamp;              // 上舰时间秒级时间戳
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	bool fans_medal_wearing_status; // 佩戴的粉丝勋章佩戴状态
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString guard_unit;         // 大航海单位
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString fans_medal_name;    // 粉丝勋章名
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString msg_id;             // 消息唯一id
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FUserInfo user_info;             // 用户信息
	
	explicit FGuardBuyData(const nlohmann::json& jsonData);
	FGuardBuyData() = default;
	void setValue(const nlohmann::json& jsonData);
};

// 付费留言
USTRUCT(BlueprintType)
struct FSuperChatData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 room_id;                // 直播间id
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 uid;                    // 购买用户UID
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 message_id;             // 留言id(风控场景下撤回留言需要)
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 rmb;                    // 支付金额(元)
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 timestamp;              // 赠送时间秒级
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 start_time;             // 生效开始时间
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 end_time;               // 生效结束时间
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 guard_level;            // 对应房间大航海等级
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 fans_medal_level;       // 对应房间勋章信息
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	bool fans_medal_wearing_status; // 当前佩戴的粉丝勋章佩戴状态
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString uname;              // 购买的用户昵称
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString uface;              // 购买用户头像
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString message;            // 留言内容
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString fans_medal_name;    // 对应房间勋章名字
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString msg_id;             // 消息唯一id

	explicit FSuperChatData(const nlohmann::json& jsonData);
	FSuperChatData() = default;
	void setValue(const nlohmann::json& jsonData);
};

//过时的付费留言
struct SuperChatDelData
{

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	int64 room_id;                  // 直播间id
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = BOpenliveSDK)
	FString msg_id;               // 留言id
	
	std::vector<int64_t> message_ids; // 消息唯一id

	explicit SuperChatDelData(const nlohmann::json& jsonData);
	SuperChatDelData() = default;
	void setValue(const nlohmann::json& jsonData);
};

enum EErrorString {
	ERROR_DATA_INVAILD,				//无效数据
	ERROR_WEBSOCKET_CONNECT,		//websocket连接时出现异常
	ERROR_WEBSOCKET_DISCONNECT,		//websocket断线
};