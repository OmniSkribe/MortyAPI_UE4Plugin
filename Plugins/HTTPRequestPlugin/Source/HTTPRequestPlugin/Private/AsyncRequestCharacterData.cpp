// Fill out your copyright notice in the Description page of Project Settings.

#include "AsyncRequestCharacterData.h"

UAsyncRequestCharacterData* UAsyncRequestCharacterData::DownloadCharacerData()
{
	UAsyncRequestCharacterData* DownloadTask = NewObject<UAsyncRequestCharacterData>();
	
	FString charID = FString::FromInt(FMath::RandRange(1, 500));
	FString URL = TEXT("https://rickandmortyapi.com/api/character/" + charID);
	
	DownloadTask->Start(URL);

	return DownloadTask;
}

void UAsyncRequestCharacterData::Start(FString URL)
{
//#if !UE_SERVER
	// Create the Http request and add to pending request list
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsyncRequestCharacterData::HandleImageRequest);
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->ProcessRequest();
//#else
	//// On the server we don't execute fail or success we just don't fire the request.
	//RemoveFromRoot();
//#endif
}

void UAsyncRequestCharacterData::HandleImageRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
//#if !UE_SERVER

	//RemoveFromRoot();

	if (bSucceeded && HttpResponse.IsValid() && HttpResponse->GetContentLength() > 0)
	{
	//	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	//	TSharedPtr<IImageWrapper> ImageWrappers[3] =
	//	{
	//		ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG),
	//		ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG),
	//		ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP),
	//	};

	//	for (auto ImageWrapper : ImageWrappers)
	//	{
	//		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(HttpResponse->GetContent().GetData(), HttpResponse->GetContentLength()))
	//		{
	//			TArray64<uint8>* RawData = new TArray64<uint8>();
	//			const ERGBFormat InFormat = ERGBFormat::BGRA;
	//			if (ImageWrapper->GetRaw(InFormat, 8, *RawData))
	//			{
	//				if (UTexture2DDynamic* Texture = UTexture2DDynamic::Create(ImageWrapper->GetWidth(), ImageWrapper->GetHeight()))
	//				{
	//					Texture->SRGB = true;
	//					Texture->UpdateResource();

	//					FTexture2DDynamicResource* TextureResource = static_cast<FTexture2DDynamicResource*>(Texture->Resource);
	//					if (TextureResource)
	//					{
	//						ENQUEUE_RENDER_COMMAND(FWriteRawDataToTexture)(
	//							[TextureResource, RawData](FRHICommandListImmediate& RHICmdList)
	//							{
	//								WriteRawToTexture_RenderThread(TextureResource, RawData);
	//							});
	//					}
	//					else
	//					{
	//						delete RawData;
	//					}
	//					OnSuccess.Broadcast(Texture);
	//					return;
	//				}
	//			}
	//		}
	//	}

		FCharacterData local_data;

		UE_LOG(LogTemp, Warning, TEXT("REQUEST RECIEVED"));
		TSharedRef<IHttpResponse, ESPMode::ThreadSafe> respond = HttpResponse.ToSharedRef();
		FString str = HttpResponse->GetContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *HttpResponse->GetContentAsString());

		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef< TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		//TSharedRef< TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create();

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		{

			//TSharedPtr<FJsonObject> jsonObj = JsonObject->GetObjectField("results");
			//FString char_name = jsonObj->GetStringField("name");

			local_data.Character_Name = FText::FromString( JsonObject->GetStringField("name") );
			local_data.Character_Status = FText::FromString(JsonObject->GetStringField("status"));
			local_data.Character_Species = FText::FromString(JsonObject->GetStringField("species"));
			local_data.Character_Gender = FText::FromString(JsonObject->GetStringField("gender"));
			local_data.Character_Origin_Name = FText::FromString(JsonObject->GetObjectField("origin")->GetStringField("name"));
			local_data.Character_Image_URL = FText::FromString(JsonObject->GetStringField("image"));

			requested_data.Character_Name = FText::FromString(JsonObject->GetStringField("name"));

			//UE_LOG(LogTemp, Warning, TEXT("Character: %s, %s, %s"), *char_name, *char_species, *char_image);
			//UE_LOG(LogTemp, Warning, TEXT("Origin2: %s"), *origin_name);

			OnSuccess.Broadcast(local_data);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Something wrong"));
			//OnFail.Broadcast(nullptr);
		}
	}


//#endif
}