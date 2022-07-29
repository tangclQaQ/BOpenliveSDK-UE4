#pragma once

#include <string>
#include <vector>
#include "Tool/json.hpp"
#include <stdint.h>

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
struct DanmaData
{
	int64_t uid;                    // 用户UID
	int64_t timestamp;              // 弹幕发送时间秒级时间戳
	int64_t room_id;                // 弹幕接收的直播间
	int64_t guard_level;            // 对应房间大航海等级
	int64_t fans_medal_level;       // 对应房间勋章信息
	FString msg_id;             // 消息唯一id
	bool fans_medal_wearing_status; // 当前佩戴的粉丝勋章佩戴状态
	FString uname;              // 用户昵称
	FString uface;              // 用户头像
	FString msg;                // 弹幕内容
	FString fans_medal_name;    // 粉丝勋章名

	explicit DanmaData(const nlohmann::json& jsonData);
	DanmaData() = default;
	void setValue(const nlohmann::json& jsonData);
};

struct UserInfo
{
	int64_t uid;       // 收礼主播uid
	FString uname; // 收礼主播昵称
	FString uface; // 收礼主播头像
};

// 礼物
struct GiftData
{
	int64_t room_id;                // 房间号
	int64_t uid;                    // 送礼用户UID
	int64_t gift_id;                // 道具id(盲盒:爆出道具id)
	int64_t gift_num;               // 赠送道具数量
	int64_t price;                  // 支付金额(1000 = 1元 = 10电池),盲盒:爆出道具的价值
	int64_t fans_medal_level;       // 实际送礼人的勋章信息
	int64_t guard_level;            // 大航海等级
	int64_t timestamp;              // 收礼时间秒级时间戳
	bool paid;                      // 是否是付费道具
	bool fans_medal_wearing_status; // 当前佩戴的粉丝勋章佩戴状态
	FString uname;              //送礼用户昵称
	FString uface;              // 送礼用户头像
	FString gift_name;          // 道具名(盲盒:爆出道具名)
	FString fans_medal_name;    //粉丝勋章名
	FString msg_id;             // 消息唯一id
	UserInfo anchor_info;           // 主播信息

	explicit GiftData(const nlohmann::json& jsonData);
	GiftData() = default;
	void setValue(const nlohmann::json& jsonData);
};

// 大航海
struct GuardBuyData
{
	int64_t guard_level;            // 大航海等级
	int64_t guard_num;              // 大航海数量
	int64_t fans_medal_level;       // 粉丝勋章等级
	int64_t room_id;                // 房间号
	int64_t timestamp;              // 上舰时间秒级时间戳
	bool fans_medal_wearing_status; // 佩戴的粉丝勋章佩戴状态
	FString guard_unit;         // 大航海单位
	FString fans_medal_name;    // 粉丝勋章名
	FString msg_id;             // 消息唯一id
	UserInfo user_info;             // 用户信息
	explicit GuardBuyData(const nlohmann::json& jsonData);
	GuardBuyData() = default;
	void setValue(const nlohmann::json& jsonData);
};

// 付费留言
struct SuperChatData
{
	int64_t room_id;                // 直播间id
	int64_t uid;                    // 购买用户UID
	int64_t message_id;             // 留言id(风控场景下撤回留言需要)
	int64_t rmb;                    // 支付金额(元)
	int64_t timestamp;              // 赠送时间秒级
	int64_t start_time;             // 生效开始时间
	int64_t end_time;               // 生效结束时间
	int64_t guard_level;            // 对应房间大航海等级
	int64_t fans_medal_level;       // 对应房间勋章信息
	bool fans_medal_wearing_status; // 当前佩戴的粉丝勋章佩戴状态
	FString uname;              // 购买的用户昵称
	FString uface;              // 购买用户头像
	FString message;            // 留言内容
	FString fans_medal_name;    // 对应房间勋章名字
	FString msg_id;             // 消息唯一id

	explicit SuperChatData(const nlohmann::json& jsonData);
	SuperChatData() = default;
	void setValue(const nlohmann::json& jsonData);
};

struct SuperChatDelData
{
	int64_t room_id;                  // 直播间id
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