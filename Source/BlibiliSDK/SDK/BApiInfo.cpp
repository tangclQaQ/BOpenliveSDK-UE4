#include "BApiInfo.h"
/*
 * 定义一些sdk使用的数据格式
 */
ApiInfo::ApiInfo(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void ApiInfo::setValue(const nlohmann::json& jsonData)
{
	this->roomId = jsonData["anchor_info"]["room_id"].get<int>();
	this->uid = jsonData["anchor_info"]["uid"].get<int>();
	this->uface = jsonData["anchor_info"]["uface"].get<std::string>();
	this->uname = jsonData["anchor_info"]["uname"].get<std::string>();
	this->gameId = jsonData["game_info"]["game_id"].get<std::string>();
	this->authBody = jsonData["websocket_info"]["auth_body"].get<std::string>();
	for (int index = 0; index < jsonData["websocket_info"]["wss_link"].size(); ++index)
	{
		this->wssLink.push_back(jsonData["websocket_info"]["wss_link"][0].get<std::string>());
	}
}

// 弹幕
DanmaData::DanmaData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void DanmaData::setValue(const nlohmann::json& jsonData)
{
	uid = jsonData["uid"].get<int64_t>();
	timestamp = jsonData["timestamp"].get<int64_t>();
	room_id = jsonData["room_id"].get<int64_t>();
	guard_level = jsonData["guard_level"].get<int64_t>();
	fans_medal_level = jsonData["fans_medal_level"].get<int64_t>();
	msg_id = jsonData["msg_id"].get<std::string>();
	fans_medal_wearing_status = jsonData["fans_medal_wearing_status"].get<bool>();
	uname = jsonData["uname"].get<std::string>();
	uface = jsonData["uface"].get<std::string>();
	msg = jsonData["msg"].get<std::string>();
	fans_medal_name = jsonData["fans_medal_name"].get<std::string>();
}

// 礼物
GiftData::GiftData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void GiftData::setValue(const nlohmann::json& jsonData)
{
	room_id = jsonData["room_id"].get<int64_t>();
	uid = jsonData["uid"].get<int64_t>();
	gift_id = jsonData["gift_id"].get<int64_t>();
	gift_num = jsonData["gift_num"].get<int64_t>();
	price = jsonData["price"].get<int64_t>();
	fans_medal_level = jsonData["fans_medal_level"].get<int64_t>();
	guard_level = jsonData["guard_level"].get<int64_t>();
	timestamp = jsonData["timestamp"].get<int64_t>();
	paid = jsonData["paid"].get<bool>();
	fans_medal_wearing_status = jsonData["fans_medal_wearing_status"].get<bool>();
	uname = jsonData["uname"].get<std::string>();
	uface = jsonData["uface"].get<std::string>();
	gift_name = jsonData["gift_name"].get<std::string>();
	fans_medal_name = jsonData["fans_medal_name"].get<std::string>();
	msg_id = jsonData["msg_id"].get<std::string>();

	anchor_info.uid = jsonData["anchor_info"]["uid"].get<int64_t>();
	anchor_info.uface = jsonData["anchor_info"]["uface"].get<std::string>();
	anchor_info.uname = jsonData["anchor_info"]["uname"].get<std::string>();
}

// 大航海
GuardBuyData::GuardBuyData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void GuardBuyData::setValue(const nlohmann::json& jsonData)
{
	guard_level = jsonData["guard_level"].get<int64_t>();
	guard_num = jsonData["guard_num"].get<int64_t>();
	fans_medal_level = jsonData["fans_medal_level"].get<int64_t>();
	room_id = jsonData["room_id"].get<int64_t>();
	timestamp = jsonData["timestamp"].get<int64_t>();
	fans_medal_wearing_status = jsonData["fans_medal_wearing_status"].get<bool>();
	guard_unit = jsonData["guard_unit"].get<std::string>();
	fans_medal_name = jsonData["fans_medal_name"].get<std::string>();
	msg_id = jsonData["msg_id"].get<std::string>();

	user_info.uid = jsonData["user_info"]["uid"].get<int64_t>();
	user_info.uface = jsonData["user_info"]["uface"].get<std::string>();
	user_info.uname = jsonData["user_info"]["uname"].get<std::string>();
}

// 付费留言
SuperChatData::SuperChatData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void SuperChatData::setValue(const nlohmann::json& jsonData)
{
	room_id = jsonData["room_id"].get<int64_t>();
	uid = jsonData["uid"].get<int64_t>();
	message_id = jsonData["message_id"].get<int64_t>();
	rmb = jsonData["rmb"].get<int64_t>();
	timestamp = jsonData["timestamp"].get<int64_t>();
	start_time = jsonData["start_time"].get<int64_t>();
	end_time = jsonData["end_time"].get<int64_t>();
	guard_level = jsonData["guard_level"].get<int64_t>();
	fans_medal_level = jsonData["fans_medal_level"].get<int64_t>();
	fans_medal_wearing_status = jsonData["fans_medal_wearing_status"].get<bool>();
	uname = jsonData["uname"].get<std::string>();
	uface = jsonData["uface"].get<std::string>();
	message = jsonData["message"].get<std::string>();
	fans_medal_name = jsonData["fans_medal_name"].get<std::string>();
	msg_id = jsonData["msg_id"].get<std::string>();
}

SuperChatDelData::SuperChatDelData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void SuperChatDelData::setValue(const nlohmann::json& jsonData)
{
	room_id = jsonData["room_id"].get<int64_t>();
	msg_id = jsonData["msg_id"].get<std::string>();
	message_ids.clear();
	for (int index = 0; index < jsonData["message_ids"].size(); ++index)
	{
		message_ids.push_back(jsonData["message_ids"][index].get<int64_t>());
	}
}
