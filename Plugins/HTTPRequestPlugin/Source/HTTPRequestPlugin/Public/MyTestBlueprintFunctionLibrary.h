// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"

#include "MyTestBlueprintFunctionLibrary.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHttpRequestCompleted, const FString&, Name, bool, bSuccess);

UCLASS()
class HTTPREQUESTPLUGIN_API UMyTestBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Test")
	void SomeTestFunction();

	//UFUNCTION(BlueprintCallable, Category = "Test")
	void GetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
