// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "TestHttpActor.generated.h"


UCLASS()
class CODINGTEST_API ATestHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	FHttpModule* Http;
	FString ApiBaseUrl = "https://api.nasa.gov/insight_weather/?api_key=vEfWHbbmx4bLyJLSAPbbcH5vnw8CaKTqsNvrO5Kf&feedtype=json&ver=1.0";
	// Sets default values for this actor's properties
	ATestHttpActor();
	
	UFUNCTION()
	void MyHttpCall();
	
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
