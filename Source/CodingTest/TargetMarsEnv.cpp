// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetMarsEnv.h"
#include "Kismet/GameplayStatics.h"
#include "MarsWeatherHandler.h"

// Sets default values
ATargetMarsEnv::ATargetMarsEnv()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	AtmosphericTemperatureIndicator = CreateDefaultSubobject<UPointLightComponent>("AtmosphericTemperature");
	HorizontalWindSpeedIndicator = CreateDefaultSubobject<UPointLightComponent>("HorizontalWindSpeedIndicator");
	AtmosphericPressureIndicator = CreateDefaultSubobject<UPointLightComponent>("AtmosphericPressure");

	BaseMesh->SetupAttachment(RootComponent);
	AtmosphericPressureIndicator->SetupAttachment(RootComponent);
	HorizontalWindSpeedIndicator->SetupAttachment(RootComponent);
	AtmosphericPressureIndicator->SetupAttachment(RootComponent);

	
	AtmosphericTemperatureIndicator->SetLightColor(FLinearColor::Red);
	AtmosphericTemperatureIndicator->SetIntensity(0.0f);

	HorizontalWindSpeedIndicator->SetLightColor(FLinearColor::Green);
	HorizontalWindSpeedIndicator->SetIntensity(0.0f);

	AtmosphericPressureIndicator->SetLightColor(FLinearColor::Blue);
	AtmosphericPressureIndicator->SetIntensity(0.0f);
}

void ATargetMarsEnv::FloatValueChanged(const FString& ValueCategory, float Start, float End)
{
	
}

void ATargetMarsEnv::UpdateSeason(const FString& Season)
{
	SeasonText->SetText(Season); 
}

// Called when the game starts or when spawned
void ATargetMarsEnv::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> MarsWeatherHandlers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMarsWeatherHandler::StaticClass(), MarsWeatherHandlers);
	if (MarsWeatherHandlers.Num() != 0)
	{
		auto MarsWeatherHandler = Cast<AMarsWeatherHandler>(MarsWeatherHandlers[0]);
		FloatDelegateHandle = MarsWeatherHandler->OnFloatChanged.AddUObject(this, &ATargetMarsEnv::FloatValueChanged);
		SeasonDelegateHandle = MarsWeatherHandler->OnSeasonChange.AddUObject(this, &ATargetMarsEnv::UpdateSeason);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No MarsWeatherHandlers Found!"));
	}
}

// Called every frame
void ATargetMarsEnv::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

