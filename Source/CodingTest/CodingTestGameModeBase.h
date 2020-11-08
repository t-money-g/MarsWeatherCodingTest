// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CodingTestGameModeBase.generated.h"	

DECLARE_DELEGATE_OneParam(FParamDelegateSignature, FLinearColor);

USTRUCT()
struct FWeatherParam
{
	GENERATED_BODY();

	UPROPERTY()
    float AV;

	UPROPERTY()
    int32 CT;

	UPROPERTY()
    float MN;

	UPROPERTY()
    float MX; 
};

USTRUCT()
struct FWindDirection
{
	GENERATED_BODY();

	UPROPERTY()
    float Compass_Degrees;

	UPROPERTY()
    FString Compass_Point;

	UPROPERTY()
    double Compass_Right;

	UPROPERTY()
    double Compass_Up;

	UPROPERTY()
    int32 ct; 
};

USTRUCT()
struct FWeatherData
{
	GENERATED_BODY();

	UPROPERTY()
	FString SolKey;
	
	UPROPERTY() 
    FWeatherParam AT;

	UPROPERTY()
    FWeatherParam HWS;

	UPROPERTY()
    FWeatherParam PRE;

	UPROPERTY()
    FWindDirection WD;

	UPROPERTY()
    FDateTime FirstUTC;

	UPROPERTY()
    FDateTime LastUTC;

	UPROPERTY()
    FString Season; 
};

USTRUCT(BlueprintType)
struct FSolKeys
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<FString> sol_keys; 
};
/**
 * 
 */
UCLASS()
class CODINGTEST_API ACodingTestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	FParamDelegateSignature AParameterDelegate;
	
	TArray<FWeatherData> CurrentWeatherData;

	FSolKeys SolKeys;

	void LoadDataFromJsonObject(TSharedPtr<FJsonObject> JsonObject);

public:
	virtual void BeginPlay() override; 

	TArray<FWeatherData>& GetWeatherData() { return CurrentWeatherData; };   

};
