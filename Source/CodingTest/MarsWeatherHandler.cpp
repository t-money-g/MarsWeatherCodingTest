// Fill out your copyright notice in the Description page of Project Settings.


#include "MarsWeatherHandler.h"
#include "Kismet/GameplayStatics.h"
#include "CodingTestGameModeBase.h"

// Sets default values
AMarsWeatherHandler::AMarsWeatherHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TimeScale = 5;
	ElapsedDays = 0;
	
}

TArray<FWeatherData> AMarsWeatherHandler::GetWeatherDataFromGameMode()
{
	UWorld* World = GetWorld();

	if(World != nullptr)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
		ACodingTestGameModeBase *CurrentGameMode = Cast<ACodingTestGameModeBase>(GameMode);

		if (CurrentGameMode != nullptr)
		{
			return CurrentGameMode->GetWeatherData();
		}
	}
	
	return TArray<FWeatherData>();
}

// Called when the game starts or when spawned
void AMarsWeatherHandler::BeginPlay()
{
	Super::BeginPlay();
	CachedWeatherData = GetWeatherDataFromGameMode();
}

// Called every frame
void AMarsWeatherHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ElapsedDays += (DeltaTime * TimeScale);

	if(ElapsedDays > 5)
	{
		ElapsedDays -= 5;
	}

	for(auto WeatherData : CachedWeatherData)
	{
		// Loop through the weather data 
		// get a reference to the WeatherData and call the appropriate functions , e.g: 
		// OnFloatValueChanged.Broadcast(AT, Previous, Current )
		// OnSeasonChange(NextSeason) 
	}
	
}

