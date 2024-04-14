// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FindLocationInGroup.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UBTT_FindLocationInGroup : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_FindLocationInGroup(FObjectInitializer const& a_pObjectInit);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem);
};
