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
typedef unsigned char danmakuByte;
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
	int toInt(danmakuByte* buffer, int index);
	int toShort(danmakuByte* buffer, int index);
	void heartBeat();

private:
	TSharedPtr<IWebSocket> Socket;
	ApiInfo m_apiInfo;
	FTimerHandle m_beatTimer;
	danmakuByte unzipBuffer[UNZIP_BUFF_SIZE];
};

