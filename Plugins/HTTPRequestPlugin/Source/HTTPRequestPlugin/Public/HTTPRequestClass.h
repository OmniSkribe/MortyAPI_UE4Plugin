// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTPRequestClass.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HTTPREQUESTPLUGIN_API UHTTPRequestClass : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void TestFunction();
};
