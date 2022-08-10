// Copyright 2022 Tangcl, Inc. All Rights Reserved.

#pragma once
#include <string>
#include <functional>
#include "Interfaces/IHttpRequest.h"

typedef void(*CallBack)(bool isSuccess, const std::string &);

class BApi
{
private:
	const std::string OpenLiveDomain = "https://live-open.biliapi.com";
	const std::string RoomIdApi = "/v1/common/roomIdInfo";
	const std::string InteractivePlayStart = "/v2/app/start";
	const std::string InteractivePlayEnd = "/v2/app/end";
	const std::string InteractivePlayHeartBeat = "/v2/app/heartbeat";
	const std::string InteractivePlayBatchHeartBeat = "/v2/app/batchHeartbeat";
private:
	std::string m_accessKeyId;
	std::string m_accessKeySecret;
private:
	void ApiPost(const std::string& url, const std::string& bodyData, CallBack callback);
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 27) || (ENGINE_MAJOR_VERSION == 5)
	void ApiSetReqHeader(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> &request, const std::string &bodyData);
#else
	void ApiSetReqHeader(TSharedRef<IHttpRequest> &request, const std::string &bodyData);
#endif

public:
	BApi(const std::string &accessKeyId, const std::string &accessKeySecret);
	inline void StartInteractivePlay(const std::string &code, const std::string &appId, CallBack callback)
	{
		ApiPost("https://live-open.biliapi.com/v2/app/start", (std::string("{\"code\":\"") + code + "\",\"app_id\":" + appId + "}"), callback);
	}

	inline void HeartBeatInteractivePlay(const std::string &gameId, CallBack callback)
	{
		ApiPost((OpenLiveDomain + InteractivePlayHeartBeat), (std::string("{\"game_id\":\"") + gameId + "\"}"), callback);
	}

	inline void EndInteractivePlay(const std::string &appId, const std::string &gameId, CallBack callback)
	{
		ApiPost((OpenLiveDomain + InteractivePlayEnd), (std::string("{\"app_id\":") + appId + ",\"game_id\":\"" + gameId + "\"}"), callback);
	}
};
