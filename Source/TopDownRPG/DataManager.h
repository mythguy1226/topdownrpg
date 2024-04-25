// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataManager.generated.h"

class FJsonObject;

USTRUCT(BlueprintType)
struct FSaveData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int PlayerLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int TotalKills;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int PlayerXP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> EquippedSpells;
};

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UDataManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static FString GenerateUUID();

	UFUNCTION(BlueprintCallable)
	static void WriteSaveDataToJsonFile(FString JsonFilePath, FSaveData Data, bool& bOutSuccess, FString& OutInfoMessage);
public:
	static void WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage);
	static void WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage);
};
