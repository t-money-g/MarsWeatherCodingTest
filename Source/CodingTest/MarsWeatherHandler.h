// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CodingTestGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MarsWeatherHandler.generated.h"

// Declaring multicast delegates to broadcast weather changes to any actors listening. 

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFloatValueChangedSignature, const FString&, float, float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSeasonChange, const FString&)

UCLASS()
class CODINGTEST_API AMarsWeatherHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMarsWeatherHandler();

	UPROPERTY()
	int32 TimeScale;
	
	UPROPERTY()
	float ElapsedDays; 

	UPROPERTY()
	TArray<FDateTime> AvailableStartTimes;

	UPROPERTY()
	TArray<FDateTime> AvailableEndTimes;

	FDateTime CurrentTime; 

	FOnFloatValueChangedSignature OnFloatChanged;
	
	FOnSeasonChange OnSeasonChange;

	TArray<FWeatherData> GetWeatherDataFromGameMode(); 

	TArray<FWeatherData> CachedWeatherData; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
