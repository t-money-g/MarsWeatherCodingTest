// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Components/TextRenderComponent.h"

#include "TargetMarsEnv.generated.h"

/*
 * This class simply listens for changes in weather over an interval set
 * by weather handler
 */
UCLASS(BlueprintType)
class CODINGTEST_API ATargetMarsEnv : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetMarsEnv();

	UPROPERTY(EditDefaultsOnly)
    UPointLightComponent* AtmosphericTemperatureIndicator;

	UPROPERTY(EditDefaultsOnly)
	UPointLightComponent* HorizontalWindSpeedIndicator;

	UPROPERTY(EditDefaultsOnly)
    UPointLightComponent* AtmosphericPressureIndicator;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* DirectionComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;
	
	UFUNCTION()
	void FloatValueChanged(const FString& ValueCategory, float Start, float End);

	FDelegateHandle FloatDelegateHandle;
	FDelegateHandle SeasonDelegateHandle;

	
	UTextRenderComponent* SeasonText;

	UFUNCTION()
	void UpdateSeason(const FString& Season); 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
