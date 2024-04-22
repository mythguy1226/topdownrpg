// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_FindClosestGroupMember.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBTS_FindClosestGroupMember : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	// Constructor
	UBTS_FindClosestGroupMember();

	// Method for when service is called
	void OnBecomeRelevant(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem);
};
