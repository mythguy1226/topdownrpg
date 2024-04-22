// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_TurnToFaceEnemyInRange.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBTT_TurnToFaceEnemyInRange : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_TurnToFaceEnemyInRange(FObjectInitializer const& a_pObjectInit);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem);

	UPROPERTY(EditAnywhere, Category = Blackboard)
	float Range = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LookRotationRate = 0.25f;
};
