#include "BSdk.h"

UBSdk*	UBSdk::s_UBSdk = nullptr;
UBSdk::~UBSdk()
{
	if (bapi != nullptr) {
        delete bapi;
        bapi = nullptr;
    }
    if (danMuQWebsocket != nullptr) {
        delete danMuQWebsocket;
        danMuQWebsocket = nullptr;
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
	if (danMuQWebsocket != nullptr) {
		delete danMuQWebsocket;
		danMuQWebsocket = nullptr;
	}
	danMuQWebsocket = NewObject<UBWebsocket>(this);
	danMuQWebsocket->init(apiInfo, WebSocketError, WebSocketMessage);
}

void UBSdk::WebSocketError(EErrorString error)
{
	
}

void UBSdk::WebSocketMessage(std::string string)
{
	
}
