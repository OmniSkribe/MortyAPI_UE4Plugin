// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "AsyncRequestCharacterData.generated.h"


USTRUCT(BlueprintType)
struct FCharacterData {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FText Character_Id;
	
	UPROPERTY(BlueprintReadOnly)
	FText Character_Name;

	UPROPERTY(BlueprintReadOnly)
	FText Character_Status;

	UPROPERTY(BlueprintReadOnly)
	FText Character_Species;

	UPROPERTY(BlueprintReadOnly)
	FText Character_Gender;

	UPROPERTY(BlueprintReadOnly)
	FText Character_Origin_Name;
	
	UPROPERTY(BlueprintReadOnly)
	FText Character_Image_URL;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDownloadDataDelegate, FCharacterData, Data);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDownloadDataDelegate, FString, Name, FCharacterData, Data);

UCLASS()
class HTTPREQUESTPLUGIN_API UAsyncRequestCharacterData : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// Why return class object?
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncRequestCharacterData* DownloadCharacerData();

	void Start(FString URL);

	UPROPERTY(BlueprintAssignable)
	FDownloadDataDelegate OnSuccess;
protected:
	FCharacterData requested_data;

private:
	// Handles data requests coming from the web
	void HandleImageRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};
