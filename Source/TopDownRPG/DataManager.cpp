// Fill out your copyright notice in the Description page of Project Settings.


#include "DataManager.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "Misc/Guid.h"

FString UDataManager::GenerateUUID()
{
	// Create a new uuid and return it
	FGuid guid = FGuid::NewGuid();
	return guid.ToString();
}

void UDataManager::WriteSaveDataToJsonFile(FString JsonFilePath, FSaveData Data, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Try to convert save struct to generic json object
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Data);
	if (!JsonObject)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write save data to Json failed - was not able to convert the struct to a json object"));
		return;
	}

	// Write to the json file
	WriteJson(JsonFilePath, JsonObject, bOutSuccess, OutInfoMessage);
}

void UDataManager::WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Try to write the string into a file
	if (!FFileHelper::SaveStringToFile(String, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write String to File Failed - Was not able to write to file. Is your file read only? Is the path valid? - '%s'"), *FilePath);
		return;
	}

	// Successful write
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write String to file succeeded - '%s'"), *FilePath);
}

void UDataManager::WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage)
{
	FString JsonString;

	// Try to convert json object to string and output the result to JsonString
	if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonString, 0)))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write Json Failed - Was not able to serialize the json to string. is the JsonObject valid?"));
		return;
	}

	// try to write json string to file
	WriteStringToFile(JsonFilePath, JsonString, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return;
	}

	// Successful json write
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write Json Succeeded - '%s'"), *JsonFilePath);
}
