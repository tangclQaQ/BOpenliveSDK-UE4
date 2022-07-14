// Copyright Epic Games, Inc. All Rights Reserved.


#include "BlibiliSDKGameModeBase.h"


ABlibiliSDKGameModeBase::ABlibiliSDKGameModeBase(){
	UBSdk::GetInstancePtr()->init("aLxyPrDjVh6TvHKTqQ3JzTJA", "sYZI8xpmRzpGHugy3ijg9Zwzs3MeiC", "1654051873246", "BL65NMPPX0XS7");
	UBSdk::GetInstancePtr()->Start();
}
