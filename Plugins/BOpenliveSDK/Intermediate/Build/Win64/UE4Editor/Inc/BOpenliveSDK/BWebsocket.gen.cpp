// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BOpenliveSDK/Public/BWebsocket.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBWebsocket() {}
// Cross Module References
	BOPENLIVESDK_API UClass* Z_Construct_UClass_UBWebsocket_NoRegister();
	BOPENLIVESDK_API UClass* Z_Construct_UClass_UBWebsocket();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_BOpenliveSDK();
// End Cross Module References
	void UBWebsocket::StaticRegisterNativesUBWebsocket()
	{
	}
	UClass* Z_Construct_UClass_UBWebsocket_NoRegister()
	{
		return UBWebsocket::StaticClass();
	}
	struct Z_Construct_UClass_UBWebsocket_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBWebsocket_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_BOpenliveSDK,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBWebsocket_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BWebsocket.h" },
		{ "ModuleRelativePath", "Public/BWebsocket.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBWebsocket_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBWebsocket>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBWebsocket_Statics::ClassParams = {
		&UBWebsocket::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBWebsocket_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBWebsocket_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBWebsocket()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBWebsocket_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBWebsocket, 1726888810);
	template<> BOPENLIVESDK_API UClass* StaticClass<UBWebsocket>()
	{
		return UBWebsocket::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBWebsocket(Z_Construct_UClass_UBWebsocket, &UBWebsocket::StaticClass, TEXT("/Script/BOpenliveSDK"), TEXT("UBWebsocket"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBWebsocket);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
