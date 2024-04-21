// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_AttackEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBTT_AttackEnemy : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_AttackEnemy(FObjectInitializer const& a_pObjectInit);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem);

	UPROPERTY(EditAnywhere, Category = Blackboard)
	float AttackRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Attack;

	// Blackboard key selector for whether AI can attack or not
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector CanAttackBlackboardKey;
};
