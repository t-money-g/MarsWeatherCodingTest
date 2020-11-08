// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHttpActor.h"

// Sets default values
ATestHttpActor::ATestHttpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	Http = &FHttpModule::Get();
}

void ATestHttpActor::MyHttpCall()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ATestHttpActor::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL("https://api.nasa.gov/insight_weather/?api_key=vEfWHbbmx4bLyJLSAPbbcH5vnw8CaKTqsNvrO5Kf&feedtype=json&ver=1.0");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void ATestHttpActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	UE_LOG(LogTemp, Warning, TEXT("Http response %d, %s"),
			Response->GetResponseCode(), *Response->GetContentAsString());
	//Deserialize the json data given Reader and the actual object to deserialize
	
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		TArray<TSharedPtr<FJsonValue>> sol_keys  = JsonObject->GetArrayField("sol_keys");
		for(auto v : sol_keys)
		{
			FString key ="";

			if(v->TryGetString(key))
			{
				GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, key);
			}
		}

		//Output it to the engine
		//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
	}
}

// Called when the game starts or when spawned
void ATestHttpActor::BeginPlay()
{

	Super::BeginPlay();
	MyHttpCall();
		
}

// Called every frame
void ATestHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

