// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	
};
