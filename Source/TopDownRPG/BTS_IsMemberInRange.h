// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_IsMemberInRange.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBTS_IsMemberInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	// Constructor
	UBTS_IsMemberInRange();

	// Method for when service is called
	void OnBecomeRelevant(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem);

	// Field for range
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float m_fRange = 100.0f;

	// Blackboard key selector for group member reference
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector MemberBlackboardKey;
};
