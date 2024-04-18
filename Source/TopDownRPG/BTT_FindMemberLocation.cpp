// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindMemberLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UBTT_FindMemberLocation::UBTT_FindMemberLocation(FObjectInitializer const& a_pObjectInit)
{
	NodeName = TEXT("Find Member Location");
}

EBTNodeResult::Type UBTT_FindMemberLocation::ExecuteTask(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem)
{
	// Get Nav System
	UNavigationSystemV1* pNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	// Get player reference
	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APawn* pPlayer = pPlayerController->GetPawn();

	// Get blackboard from ai controller
	UBlackboardComponent* pBlackboard = Cast<UBlackboardComponent>(a_pTreeComp.GetAIOwner()->GetComponentByClass(UBlackboardComponent::StaticClass()));

	if (pNavSystem)
	{
		// Get group member from the board
		AActor* pMember = Cast<AActor>(pBlackboard->GetValueAsObject(MemberBlackboardKey.SelectedKeyName));

		// Setting target location to member location
		pBlackboard->SetValueAsVector(GetSelectedBlackboardKey(), pMember->GetActorLocation());
	}

	// Finish execution
	FinishLatentTask(a_pTreeComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
