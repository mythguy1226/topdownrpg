// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_FindClosestGroupMember.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownRPGCharacter.h"

UBTS_FindClosestGroupMember::UBTS_FindClosestGroupMember()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Find Closest Group Member");
}

void UBTS_FindClosestGroupMember::OnBecomeRelevant(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem)
{
	// Super Call 
	Super::OnBecomeRelevant(a_pTreeComp, a_pNodeMem);

	// Get player reference
	ATopDownRPGCharacter* pPlayer = Cast<ATopDownRPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	// Only continue if player is valid
	if (pPlayer)
	{
		// Get blackboard from ai controller
		UBlackboardComponent* pBlackboard = Cast<UBlackboardComponent>(a_pTreeComp.GetAIOwner()->GetComponentByClass(UBlackboardComponent::StaticClass()));

		// Clear blackboard value if no group members exist
		// and return early
		if (pPlayer->Characters.Num() == 0)
		{
			pBlackboard->ClearValue(GetSelectedBlackboardKey());
			return;
		}

		// Iterate through each group member to find the closest
		AActor* pClosestCharacter = pPlayer->Characters[0];
		for (AActor* pCurChar : pPlayer->Characters)
		{
			// Get distance from self to closest character AND current character
			float fClosestDistance = FVector::Distance(a_pTreeComp.GetAIOwner()->GetPawn()->GetActorLocation(), pClosestCharacter->GetActorLocation());
			float fTestDistance = FVector::Distance(a_pTreeComp.GetAIOwner()->GetPawn()->GetActorLocation(), pCurChar->GetActorLocation());

			// If closer, set to new closest member
			if (fTestDistance < fClosestDistance)
				pClosestCharacter = pCurChar;

		}

		// Set blackboard key to the closest group member
		pBlackboard->SetValueAsObject(GetSelectedBlackboardKey(), pClosestCharacter);
	}
}
