// Copyright Epic Games, Inc. All Rights Reserved.


#include "CodingTestGameModeBase.h"

#include "JsonObjectConverter.h"

void ACodingTestGameModeBase::LoadDataFromJsonObject(TSharedPtr<FJsonObject> JsonObject)
{
     for( auto key : SolKeys.sol_keys)
            {
                FWeatherData Data;
             
                UE_LOG(LogTemp, Warning, TEXT("Keys : %s"), *key);
                Data.SolKey = key;
          
                TSharedPtr<FJsonObject> WeatherObject = JsonObject->GetObjectField(key);
                TSharedPtr<FJsonObject> ATWeatherParam  = WeatherObject->GetObjectField("AT");
                TSharedPtr<FJsonObject> HwsWeatherParam  = WeatherObject->GetObjectField("HWS");
                TSharedPtr<FJsonObject> PreWeatherParam  = WeatherObject->GetObjectField("PRE");
                
                Data.Season = WeatherObject->GetStringField("Season");
                
                FString FirstUtc = WeatherObject->GetStringField("First_UTC");
                FString LastUtc = WeatherObject->GetStringField("Last_UTC");
                FDateTime::Parse(FirstUtc,Data.FirstUTC);
                FDateTime::Parse(LastUtc,Data.LastUTC);

                if(ATWeatherParam)
                {
                    FWeatherParam AT;
                    AT.AV = ATWeatherParam->GetNumberField("av");
                    AT.CT = ATWeatherParam->GetNumberField("ct");
                    AT.MN = ATWeatherParam->GetNumberField("mn");
                    AT.MX = ATWeatherParam->GetNumberField("mx");
                    Data.AT = AT; 
                }
                
                if(HwsWeatherParam)
                {
                    FWeatherParam Hws;
                    Hws.AV = HwsWeatherParam->GetNumberField("av");
                    Hws.CT = HwsWeatherParam->GetNumberField("ct");
                    Hws.MN = HwsWeatherParam->GetNumberField("mn");
                    Hws.MX = HwsWeatherParam->GetNumberField("mx");
                    Data.HWS = Hws;
                }
                if(PreWeatherParam)
                {
                    FWeatherParam Pre;
                    Pre.AV = PreWeatherParam->GetNumberField("av");
                    Pre.CT = PreWeatherParam->GetNumberField("ct");
                    Pre.MN = PreWeatherParam->GetNumberField("mn");
                    Pre.MX = PreWeatherParam->GetNumberField("mx");
                    Data.PRE = Pre;
                }

                CurrentWeatherData.Add(Data);
            }    
}

void ACodingTestGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    // Local test 
    const FString JsonFilePath = FPaths::ProjectContentDir() + "/api.nasa.gov.json";
    FString JsonString;
    FFileHelper::LoadFileToString(JsonString, *JsonFilePath);

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

    if(FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
      
        bool parsedSuccess = FJsonObjectConverter::JsonObjectStringToUStruct<FSolKeys>(JsonString, &SolKeys,0,0);
        if(parsedSuccess)
        {
            LoadDataFromJsonObject(JsonObject);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Couldn't Parse that value")); 
        }
    }
}
