// Copyright 2022 Tangcl, Inc. All Rights Reserved.

#include "BApiInfo.h"
/*
 * 定义一些sdk使用的数据格式
 */
FApiInfo::FApiInfo(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void FApiInfo::setValue(const nlohmann::json& jsonData)
{
	this->roomId = jsonData["anchor_info"]["room_id"].get<int64_t>();
	this->uid = jsonData["anchor_info"]["uid"].get<int64_t>();
	this->open_id = FString(UTF8_TO_TCHAR(jsonData["anchor_info"]["open_id"].get<std::string>().c_str()));
	this->uface = FString(UTF8_TO_TCHAR(jsonData["anchor_info"]["uface"].get<std::string>().c_str()));
	this->uname = FString(UTF8_TO_TCHAR(jsonData["anchor_info"]["uname"].get<std::string>().c_str()));
	this->gameId = FString(UTF8_TO_TCHAR(jsonData["game_info"]["game_id"].get<std::string>().c_str()));
	this->authBody = FString(UTF8_TO_TCHAR(jsonData["websocket_info"]["auth_body"].get<std::string>().c_str()));
	for (int index = 0; index < jsonData["websocket_info"]["wss_link"].size(); ++index)
	{
		this->wssLink.push_back(jsonData["websocket_info"]["wss_link"][0].get<std::string>());
	}
}

// 弹幕
FDanmuData::FDanmuData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void FDanmuData::setValue(const nlohmann::json& jsonData)
{
	uid = jsonData["uid"].get<int64_t>();
	timestamp = jsonData["timestamp"].get<int64_t>();
	room_id = jsonData["room_id"].get<int64_t>();
	guard_level = jsonData["guard_level"].get<int64_t>();
	fans_medal_level = jsonData["fans_medal_level"].get<int64_t>();
	msg_id = FString(UTF8_TO_TCHAR(jsonData["msg_id"].get<std::string>().c_str()));
	if (jsonData.contains("fans_medal_wearing_status"))
	{
		fans_medal_wearing_status = jsonData["fans_medal_wearing_status"].get<bool>();
	}
	uname = FString(UTF8_TO_TCHAR(jsonData["uname"].get<std::string>().c_str()));
	open_id = FString(UTF8_TO_TCHAR(jsonData["open_id"].get<std::string>().c_str()));
	uface = FString(UTF8_TO_TCHAR(jsonData["uface"].get<std::string>().c_str()));
	msg = FString(UTF8_TO_TCHAR(jsonData["msg"].get<std::string>().c_str()));
	fans_medal_name = FString(UTF8_TO_TCHAR(jsonData["fans_medal_name"].get<std::string>().c_str()));
	emoji_img_url = FString(UTF8_TO_TCHAR(jsonData["emoji_img_url"].get<std::string>().c_str()));
	dm_type = jsonData["dm_type"].get<int64_t>();
}

// 礼物
FGiftData::FGiftData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void FGiftData::setValue(const nlohmann::json& jsonData)
{
	room_id = jsonData["room_id"].get<int64_t>();
	uid = jsonData["uid"].get<int64_t>();
	open_id = jsonData["open_id"].get<std::string>().c_str();
	gift_id = jsonData["gift_id"].get<int64_t>();
	gift_num = jsonData["gift_num"].get<int64_t>();
	price = jsonData["price"].get<int64_t>();
	fans_medal_level = jsonData["fans_medal_level"].get<int64_t>();
	guard_level = jsonData["guard_level"].get<int64_t>();
	timestamp = jsonData["timestamp"].get<int64_t>();
	paid = jsonData["paid"].get<bool>();
	if (jsonData.contains("fans_medal_wearing_status"))
	{
		fans_medal_wearing_status = jsonData["fans_medal_wearing_status"].get<bool>();
	}
	uname = FString(UTF8_TO_TCHAR(jsonData["uname"].get<std::string>().c_str()));
	uface = FString(UTF8_TO_TCHAR(jsonData["uface"].get<std::string>().c_str()));
	gift_name = FString(UTF8_TO_TCHAR(jsonData["gift_name"].get<std::string>().c_str()));
	fans_medal_name = FString(UTF8_TO_TCHAR(jsonData["fans_medal_name"].get<std::string>().c_str()));
	msg_id = FString(UTF8_TO_TCHAR(jsonData["msg_id"].get<std::string>().c_str()));

	anchor_info.uid = jsonData["anchor_info"]["uid"].get<int64_t>();
	anchor_info.open_id = FString(UTF8_TO_TCHAR(jsonData["anchor_info"]["open_id"].get<std::string>().c_str()));
	anchor_info.uface = FString(UTF8_TO_TCHAR(jsonData["anchor_info"]["uface"].get<std::string>().c_str()));
	anchor_info.uname = FString(UTF8_TO_TCHAR(jsonData["anchor_info"]["uname"].get<std::string>().c_str()));
}

// 大航海
FGuardBuyData::FGuardBuyData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void FGuardBuyData::setValue(const nlohmann::json& jsonData)
{
	guard_level = jsonData["guard_level"].get<int64_t>();
	guard_num = jsonData["guard_num"].get<int64_t>();
	fans_medal_level = jsonData["fans_medal_level"].get<int64_t>();
	room_id = jsonData["room_id"].get<int64_t>();
	timestamp = jsonData["timestamp"].get<int64_t>();
	if (jsonData.contains("fans_medal_wearing_status"))
	{
		fans_medal_wearing_status = jsonData["fans_medal_wearing_status"].get<bool>();
	}
	guard_unit = FString(UTF8_TO_TCHAR(jsonData["guard_unit"].get<std::string>().c_str()));
	fans_medal_name = FString(UTF8_TO_TCHAR(jsonData["fans_medal_name"].get<std::string>().c_str()));
	msg_id = FString(UTF8_TO_TCHAR(jsonData["msg_id"].get<std::string>().c_str()));

	user_info.uid = jsonData["user_info"]["uid"].get<int64_t>();
	user_info.open_id = FString(UTF8_TO_TCHAR(jsonData["user_info"]["open_id"].get<std::string>().c_str()));
	user_info.uface = FString(UTF8_TO_TCHAR(jsonData["user_info"]["uface"].get<std::string>().c_str()));
	user_info.uname = FString(UTF8_TO_TCHAR(jsonData["user_info"]["uname"].get<std::string>().c_str()));
}

// 付费留言
FSuperChatData::FSuperChatData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void FSuperChatData::setValue(const nlohmann::json& jsonData)
{
	room_id = jsonData["room_id"].get<int64_t>();
	uid = jsonData["uid"].get<int64_t>();
	open_id = FString(UTF8_TO_TCHAR(jsonData["open_id"].get<std::string>().c_str()));
	message_id = jsonData["message_id"].get<int64_t>();
	rmb = jsonData["rmb"].get<int64_t>();
	timestamp = jsonData["timestamp"].get<int64_t>();
	start_time = jsonData["start_time"].get<int64_t>();
	end_time = jsonData["end_time"].get<int64_t>();
	guard_level = jsonData["guard_level"].get<int64_t>();
	fans_medal_level = jsonData["fans_medal_level"].get<int64_t>();
	if (jsonData.contains("fans_medal_wearing_status"))
	{
		fans_medal_wearing_status = jsonData["fans_medal_wearing_status"].get<bool>();
	}
	uname = FString(UTF8_TO_TCHAR(jsonData["uname"].get<std::string>().c_str()));
	uface = FString(UTF8_TO_TCHAR(jsonData["uface"].get<std::string>().c_str()));
	message = FString(UTF8_TO_TCHAR(jsonData["message"].get<std::string>().c_str()));
	fans_medal_name = FString(UTF8_TO_TCHAR(jsonData["fans_medal_name"].get<std::string>().c_str()));
	msg_id = FString(UTF8_TO_TCHAR(jsonData["msg_id"].get<std::string>().c_str()));
}

FSuperChatDelData::FSuperChatDelData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void FSuperChatDelData::setValue(const nlohmann::json& jsonData)
{
	room_id = jsonData["room_id"].get<int64_t>();
	msg_id = FString(UTF8_TO_TCHAR(jsonData["msg_id"].get<std::string>().c_str()));
	message_ids.clear();
	for (int index = 0; index < jsonData["message_ids"].size(); ++index)
	{
		message_ids.push_back(jsonData["message_ids"][index].get<int64_t>());
	}
}

FLikeData::FLikeData(const nlohmann::json& jsonData)
{
	setValue(jsonData);
}

void FLikeData::setValue(const nlohmann::json& jsonData)
{
	uname = FString(UTF8_TO_TCHAR(jsonData["uname"].get<std::string>().c_str()));
	uid = jsonData["uid"].get<int64_t>();
	open_id = FString(UTF8_TO_TCHAR(jsonData["open_id"].get<std::string>().c_str()));
	uface = FString(UTF8_TO_TCHAR(jsonData["uface"].get<std::string>().c_str()));
	timestamp = jsonData["timestamp"].get<int64_t>();
	room_id = jsonData["room_id"].get<int64_t>();
	like_text = FString(UTF8_TO_TCHAR(jsonData["like_text"].get<std::string>().c_str()));
	fans_medal_wearing_status = jsonData["fans_medal_wearing_status"].get<bool>();
	fans_medal_name = FString(UTF8_TO_TCHAR(jsonData["fans_medal_name"].get<std::string>().c_str()));
	fans_medal_level = jsonData["fans_medal_level"].get<int64_t>();
}
