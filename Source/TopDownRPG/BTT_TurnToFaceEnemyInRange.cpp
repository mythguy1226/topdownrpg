// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_TurnToFaceEnemyInRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBTT_TurnToFaceEnemyInRange::UBTT_TurnToFaceEnemyInRange(FObjectInitializer const& a_pObjectInit)
{
	NodeName = TEXT("Turn To Face Enemy In Range");
}

EBTNodeResult::Type UBTT_TurnToFaceEnemyInRange::ExecuteTask(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem)
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
		// Get closest enemy from blackboard
		AActor* pEnemy = Cast<AActor>(pBlackboard->GetValueAsObject(GetSelectedBlackboardKey()));

		// Ensure enemy is valid
		if (!pEnemy)
			return EBTNodeResult::Succeeded;

		// Check that enemy is within specified range and turn towards them if in range
		if (FVector::Distance(pEnemy->GetActorLocation(), a_pTreeComp.GetAIOwner()->GetPawn()->GetActorLocation()) <= Range)
		{
			// Turn towards the enemy
			FVector vLookAtLoc = FVector(pEnemy->GetActorLocation().X, pEnemy->GetActorLocation().Y, a_pTreeComp.GetAIOwner()->GetPawn()->GetActorLocation().Z); 
			FRotator pRotation = UKismetMathLibrary::FindLookAtRotation(a_pTreeComp.GetAIOwner()->GetPawn()->GetActorLocation(), vLookAtLoc); 
			FRotator pSlerpRot = FQuat::Slerp(a_pTreeComp.GetAIOwner()->GetPawn()->GetActorQuat(), pRotation.Quaternion(), LookRotationRate).Rotator(); 
			a_pTreeComp.GetAIOwner()->GetPawn()->SetActorRotation(pSlerpRot);
		}
		else // Otherwise turn to match necromancer's rotation
		{
			// Match the player controller's rotation
			FRotator pRotation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorRotation();
			FRotator pSlerpRot = FQuat::Slerp(a_pTreeComp.GetAIOwner()->GetPawn()->GetActorQuat(), pRotation.Quaternion(), LookRotationRate).Rotator();
			a_pTreeComp.GetAIOwner()->GetPawn()->SetActorRotation(pSlerpRot);
		}
	}

	// Finish execution
	FinishLatentTask(a_pTreeComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
