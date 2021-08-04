// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestBlueprintFunctionLibrary.h"

void UMyTestBlueprintFunctionLibrary::SomeTestFunction() {
	UE_LOG(LogTemp, Warning, TEXT("MyTestBlueprintFunctionLibrary"));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	FString charID = FString::FromInt(FMath::RandRange(1, 500));

	//FString url = TEXT("https://rickandmortyapi.com/api/character/" + charID);
	FString url = TEXT("file:///C:/Users/Messy/Desktop/Mort.txt");

	UE_LOG(LogTemp, Warning, TEXT("URL: %s"), *url);

	Request->OnProcessRequestComplete().BindUObject(this, &UMyTestBlueprintFunctionLibrary::GetRequest);
	Request->SetURL(url);
	Request->SetVerb("GET");
	Request->ProcessRequest();

	UE_LOG(LogTemp, Warning, TEXT("CREATED REQUEST"));
}

void UMyTestBlueprintFunctionLibrary::GetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	UE_LOG(LogTemp, Warning, TEXT("REQUEST RECIEVED"));
	TSharedRef<IHttpResponse, ESPMode::ThreadSafe> respond = Response.ToSharedRef();
	FString str = Response->GetContentAsString();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef< TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(*Response->GetContentAsString());
	//TSharedRef< TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create();

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{

		//TSharedPtr<FJsonObject> jsonObj = JsonObject->GetObjectField("results");
		//FString char_name = jsonObj->GetStringField("name");
		FString char_name = JsonObject->GetStringField("name");
		FString char_image = JsonObject->GetStringField("image");
		FString char_species = JsonObject->GetStringField("species");
		FString origin_name = JsonObject->GetObjectField("origin")->GetStringField("name");

		UE_LOG(LogTemp, Warning, TEXT("Character: %s, %s, %s"), *char_name, *char_species, *char_image);
		UE_LOG(LogTemp, Warning, TEXT("Origin2: %s"), *origin_name);

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Something wrong"));
	}
}