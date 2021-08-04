// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "HTTPActor.generated.h"

UCLASS()
class MORTYPROJECT_API AHTTPActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHTTPActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void GetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
