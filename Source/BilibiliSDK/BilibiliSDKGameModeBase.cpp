// Copyright Epic Games, Inc. All Rights Reserved.


#include "BilibiliSDKGameModeBase.h"

#include "BOpenliveSDKBPLibrary.h"

void ABilibiliSDKGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UBOpenliveSDKBPLibrary::GetInstancePtr()->init("aLxyPrDjVh6TvHKTqQ3JzTJA", "sYZI8xpmRzpGHugy3ijg9Zwzs3MeiC", "1654051873246", "BSGIUUGSSQ9S7");
	UBOpenliveSDKBPLibrary::GetInstancePtr()->Start();

}

void ABilibiliSDKGameModeBase::Test(FDanmuData data)
{
	FString uname = data.uname;
	FString msg = data.msg;
	UE_LOG(LogTemp, Log, TEXT("弹幕发送者1：%s, 弹幕内容：%s"), *uname, *msg);
}
