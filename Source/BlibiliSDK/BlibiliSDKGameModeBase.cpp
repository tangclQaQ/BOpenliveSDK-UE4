// Copyright Epic Games, Inc. All Rights Reserved.


#include "BlibiliSDKGameModeBase.h"


ABlibiliSDKGameModeBase::ABlibiliSDKGameModeBase(){
	UBSdk::GetInstancePtr()->init("aLxyPrXXXXXXXqQ3JzTJA", "sYZI8xpXXXXXXXZwzs3MeiC", "16XXXXXX73246", "BSXXXXXS7");
	std::string str1 = "111";
	std::string str2 = "222";
	std::string str3 = str1 + str2;
}

void ABlibiliSDKGameModeBase::LoadMapEnd()
{
}

void ABlibiliSDKGameModeBase::BeginPlay()
{
	UBSdk::GetInstancePtr()->Start();
}
