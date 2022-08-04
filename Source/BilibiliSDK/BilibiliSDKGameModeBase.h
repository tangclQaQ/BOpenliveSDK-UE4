// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BApiInfo.h"
#include "GameFramework/GameModeBase.h"
#include "BilibiliSDKGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BILIBILISDK_API ABilibiliSDKGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	void Test(FDanmuData data);
	
};
