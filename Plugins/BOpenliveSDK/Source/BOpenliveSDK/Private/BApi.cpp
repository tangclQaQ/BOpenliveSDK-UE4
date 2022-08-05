// Copyright 2022 斑_tcl, Inc. All Rights Reserved.

#include "BApi.h"
#include "HttpModule.h"
#include "Misc/SecureHash.h"
#include "Tool/Sha256.h"
#include <ctime>
#include <map>

#include "Interfaces/IHttpResponse.h"


BApi::BApi(const std::string& accessKeyId, const std::string& accessKeySecret) : m_accessKeyId(accessKeyId),
                                                                                 m_accessKeySecret(accessKeySecret)
{
}

void BApi::ApiPost(const std::string& url, const std::string& bodyData, CallBack callback)
{
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 27) || (ENGINE_MAJOR_VERSION == 5)
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> request = FHttpModule::Get().CreateRequest();
#else
	TSharedRef<IHttpRequest> request = FHttpModule::Get().CreateRequest();
#endif
	int dataSize = bodyData.length();
	FString bodyDataString = bodyData.c_str();
	ApiSetReqHeader(request, bodyData); // 请求头签名
	request->SetURL(UTF8_TO_TCHAR(url.c_str()));
	request->SetVerb(TEXT("POST"));
	request->SetContentAsString(UTF8_TO_TCHAR(bodyData.c_str()));
	request->OnProcessRequestComplete().BindLambda([=](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (!Request.IsValid() || !Request.IsValid()) {
			callback(false, "Http Unknow error");
			return;
		}
		int32 StatusCode = Response->GetResponseCode();
		bool IsOK = EHttpResponseCodes::IsOk(StatusCode);
		if (!bWasSuccessful || !IsOK)
		{
			callback(false, "Http error,error code is " + std::to_string(StatusCode));
			return;
		}
		FString ResponseString = Response->GetContentAsString();
		callback(true, TCHAR_TO_UTF8(*ResponseString));
	});
	request->ProcessRequest();
}

// 添加验证用的请求头
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 27) || (ENGINE_MAJOR_VERSION == 5)
void BApi::ApiSetReqHeader(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& request, const std::string& bodyData)
#else
void BApi::ApiSetReqHeader(TSharedRef<IHttpRequest>& request, const std::string& bodyData)
#endif
{
	std::map<std::string, std::string> keyValuePair;

	FString uuid = FGuid::NewGuid().ToString();

	// 注意了，此处顺序很重要，但凡你改变一下任意2条的顺序位置都会导致验证不通过!!!!!
	keyValuePair["x-bili-accesskeyid"] = m_accessKeyId;
	keyValuePair["x-bili-content-md5"] = TCHAR_TO_UTF8(*FMD5::HashAnsiString(UTF8_TO_TCHAR(bodyData.data())));
	keyValuePair["x-bili-signature-method"] = "HMAC-SHA256";
	keyValuePair["x-bili-signature-nonce"] = TCHAR_TO_UTF8(*uuid);
	keyValuePair["x-bili-signature-version"] = "1.0";
	keyValuePair["x-bili-timestamp"] = std::to_string(std::time(0));

	// 字符串拼接，末尾不能出现'\n'
	std::string sig = "";
	for (auto &pair : keyValuePair)
	{
		request->SetHeader(pair.first.c_str(), pair.second.c_str());
		if (sig.length() == 0)
		{
			sig += pair.first + ":" + pair.second;
		}
		else
		{
			sig += "\n" + pair.first + ":" + pair.second;
		}
	}

	std::string auth = TCHAR_TO_UTF8(*HMAC_SHA256::Hash(m_accessKeySecret.c_str(), sig.c_str()).ToHexString());

	request->SetHeader("Accept", "application/json");
	request->SetHeader("Content-Type", "application/json");
	request->SetHeader("Authorization", auth.c_str());
}
