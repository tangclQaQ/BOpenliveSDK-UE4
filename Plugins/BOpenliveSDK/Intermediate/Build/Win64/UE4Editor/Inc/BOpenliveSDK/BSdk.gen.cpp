// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BOpenliveSDK/Public/BSdk.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBSdk() {}
// Cross Module References
	BOPENLIVESDK_API UClass* Z_Construct_UClass_UBSdk_NoRegister();
	BOPENLIVESDK_API UClass* Z_Construct_UClass_UBSdk();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_BOpenliveSDK();
// End Cross Module References
	void UBSdk::StaticRegisterNativesUBSdk()
	{
	}
	UClass* Z_Construct_UClass_UBSdk_NoRegister()
	{
		return UBSdk::StaticClass();
	}
	struct Z_Construct_UClass_UBSdk_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBSdk_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_BOpenliveSDK,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBSdk_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BSdk.h" },
		{ "ModuleRelativePath", "Public/BSdk.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBSdk_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBSdk>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBSdk_Statics::ClassParams = {
		&UBSdk::StaticClass,
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
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBSdk_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBSdk_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBSdk()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBSdk_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBSdk, 67742715);
	template<> BOPENLIVESDK_API UClass* StaticClass<UBSdk>()
	{
		return UBSdk::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBSdk(Z_Construct_UClass_UBSdk, &UBSdk::StaticClass, TEXT("/Script/BOpenliveSDK"), TEXT("UBSdk"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBSdk);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
