// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindLocationInGroup.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownRPGCharacter.h"

UBTT_FindLocationInGroup::UBTT_FindLocationInGroup(FObjectInitializer const& a_pObjectInit)
{
	NodeName = TEXT("Find Location In Group");
}

EBTNodeResult::Type UBTT_FindLocationInGroup::ExecuteTask(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem)
{
	// Get Nav System
	UNavigationSystemV1* pNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	// Get player reference
	ATopDownRPGCharacter* pPlayer = Cast<ATopDownRPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Only continue if player is valid
	if (pPlayer)
	{
		// Get blackboard from ai controller
		UBlackboardComponent* pBlackboard = Cast<UBlackboardComponent>(a_pTreeComp.GetAIOwner()->GetComponentByClass(UBlackboardComponent::StaticClass()));

		if (pNavSystem)
		{
			// Get this character's index in the player's group
			int charIndex = pPlayer->GetCharacterIndex(a_pTreeComp.GetAIOwner()->GetPawn());

			// Set character's follow location to index in group locations
			if (charIndex > -1)
			{
				pBlackboard->SetValueAsVector(GetSelectedBlackboardKey(), pPlayer->GroupLocations[charIndex]);
			}
			else
			{
				pBlackboard->SetValueAsVector(GetSelectedBlackboardKey(), a_pTreeComp.GetAIOwner()->GetPawn()->GetActorLocation());
			}
		}
	}

	// Finish execution
	FinishLatentTask(a_pTreeComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
