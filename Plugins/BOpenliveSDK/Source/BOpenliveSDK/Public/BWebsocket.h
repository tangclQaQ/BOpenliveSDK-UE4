// Copyright 2022 Tangcl, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebSocketsModule.h" // Module definition
#include "IWebSocket.h"       // Socket definition
#include "BApiInfo.h"
#include "TimerManager.h"
#include "zlib.h"
#include <memory>
#include "BWebsocket.generated.h"

#define UNZIP_BUFF_SIZE 65536
typedef void(*CALLBACKERROR)(EErrorString);
typedef void(*CALLBACKMESSAGE)(std::string);

UCLASS()
class UBWebsocket : public UObject
{
	GENERATED_BODY()

public:
	UBWebsocket();
	~UBWebsocket();

	void init(const ApiInfo& apiInfo, CALLBACKERROR CallbackError, CALLBACKMESSAGE CallbackMessage);
	void getBytesByInt(TArray<unsigned char> &buffer, int value);
	void getBytesByShort(TArray<unsigned char> &buffer, short value);
	int toInt(unsigned char* buffer, int index);
	int toShort(unsigned char* buffer, int index);
	void heartBeat();
	bool getIsConnected();

private:
	TSharedPtr<IWebSocket> Socket;
	ApiInfo m_apiInfo;
	FTimerHandle m_beatTimer;
	unsigned char unzipBuffer[UNZIP_BUFF_SIZE];
};

