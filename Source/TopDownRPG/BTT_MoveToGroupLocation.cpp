// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_MoveToGroupLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

UBTT_MoveToGroupLocation::UBTT_MoveToGroupLocation(FObjectInitializer const& a_pObjectInit)
{
	NodeName = TEXT("Move to Group Location");
}

EBTNodeResult::Type UBTT_MoveToGroupLocation::ExecuteTask(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem)
{
	// Get Nav System
	UNavigationSystemV1* pNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (pNavSystem)
	{
		// Get blackboard from ai controller
		UBlackboardComponent* pBlackboard = Cast<UBlackboardComponent>(a_pTreeComp.GetAIOwner()->GetComponentByClass(UBlackboardComponent::StaticClass()));

		// Get target location
		FVector pLocation = pBlackboard->GetValueAsVector(GetSelectedBlackboardKey());

		// Tell the AI to move towards target location
		a_pTreeComp.GetAIOwner()->MoveToLocation(pLocation);

		// Match the player controller's rotation
		FRotator pRotation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorRotation();
		FRotator pSlerpRot = FQuat::Slerp(a_pTreeComp.GetAIOwner()->GetPawn()->GetActorQuat(), pRotation.Quaternion(), LookRotationRate).Rotator();
		a_pTreeComp.GetAIOwner()->GetPawn()->SetActorRotation(pSlerpRot);
	}

	// Finish execution
	FinishLatentTask(a_pTreeComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
