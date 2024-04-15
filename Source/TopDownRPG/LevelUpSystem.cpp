// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpSystem.h"

void ULevelUpSystem::AddXP(int32 Amount)
{
    CurrentXP += Amount;

    while (CurrentXP >= GetXPToNextLevel())
    {
        CurrentXP -= GetXPToNextLevel();
        ++CurrentLevel;
    }
}

int32 ULevelUpSystem::GetCurrentXP() const
{
    return CurrentXP;
}

int32 ULevelUpSystem::GetCurrentLevel() const
{
    return CurrentLevel;
}

int32 ULevelUpSystem::GetXPToNextLevel() const
{
    return CalculateXPForNextLevel();
}

int32 ULevelUpSystem::CalculateXPForNextLevel() const
{
    if (CurrentLevel < 20)
    {
        return 5 + 10 * (CurrentLevel - 1);
    }
    else if (CurrentLevel < 40)
    {
        // XP for level 21 and above
        return 195 + 13 * (CurrentLevel - 20);
    }
    else
    {
        // XP for level 41 and above
        return 455 + 16 * (CurrentLevel - 40);
    }
}


