// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelUpSystem.generated.h"

UCLASS()
class TOPDOWNRPG_API ULevelUpSystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // add XP and handle leveling up
    UFUNCTION(BlueprintCallable)
    void AddXP(int32 Amount);

    // get current XP
    UFUNCTION(BlueprintCallable)
    int32 GetCurrentXP() const;

    // get current level
    UFUNCTION(BlueprintCallable)
    int32 GetCurrentLevel() const;

    // get XP needed for next level
    UFUNCTION(BlueprintCallable)
    int32 GetXPToNextLevel() const;

protected:
    // current XP amount
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 CurrentXP = 0;

    // current level
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 CurrentLevel = 1;
    
    // needed to reach the next level from the current one
    int32 CalculateXPForNextLevel() const;
};
