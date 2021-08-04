#include "HTTPActor.h"

// Sets default values
AHTTPActor::AHTTPActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHTTPActor::BeginPlay()
{
	Super::BeginPlay();

	//TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	//FString url = TEXT("https://rickandmortyapi.com/api/character/2");
	//Request->OnProcessRequestComplete().BindUObject(this, &AHTTPActor::GetRequest);
	//Request->SetURL(url);
	//Request->SetVerb("GET");
	//Request->ProcessRequest();

	//UE_LOG(LogTemp, Warning, TEXT("CREATED REQUEST"));

}

// Called every frame
void AHTTPActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AHTTPActor::GetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
//	UE_LOG(LogTemp, Warning, TEXT("REQUEST RECIEVED"));
//	TSharedRef<IHttpResponse, ESPMode::ThreadSafe> respond = Response.ToSharedRef();
//	//Response->
//	//Response.Get().GetContentAsString();
//	FString str = Response->GetContentAsString();
//	UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
//}

