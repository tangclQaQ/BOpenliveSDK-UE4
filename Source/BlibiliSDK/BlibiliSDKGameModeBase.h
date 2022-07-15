// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SDK/BSdk.h"
#include "BlibiliSDKGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BLIBILISDK_API ABlibiliSDKGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABlibiliSDKGameModeBase();

	UFUNCTION(BlueprintCallable)
		void LoadMapEnd();

	virtual void BeginPlay();
private:
	UBSdk * bsdk = nullptr;
};
