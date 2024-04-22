// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_AttackEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTT_AttackEnemy::UBTT_AttackEnemy(FObjectInitializer const& a_pObjectInit)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTT_AttackEnemy::ExecuteTask(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem)
{
	// Get the owning pawn and its anim instance
	UAnimInstance* pAnimInst = Cast<USkeletalMeshComponent>(a_pTreeComp.GetAIOwner()->GetPawn()->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();

	// Check that anim instance is valid
	if (!pAnimInst)
		return EBTNodeResult::Failed;

	// Get blackboard from ai controller
	UBlackboardComponent* pBlackboard = Cast<UBlackboardComponent>(a_pTreeComp.GetAIOwner()->GetComponentByClass(UBlackboardComponent::StaticClass()));

	// Get closest enemy from blackboard
	AActor* pEnemy = Cast<AActor>(pBlackboard->GetValueAsObject(GetSelectedBlackboardKey()));

	// Ensure enemy is valid
	if (!pEnemy)
		return EBTNodeResult::Succeeded;

	// Check that enemy is within specified range and attack them if in range
	if (FVector::Distance(pEnemy->GetActorLocation(), a_pTreeComp.GetAIOwner()->GetPawn()->GetActorLocation()) <= AttackRange)
	{
		// Ensure AI is able to attack
		if (pBlackboard->GetValueAsBool(CanAttackBlackboardKey.SelectedKeyName))
		{
			// Make sure attack isnt already being used
			if (!pAnimInst->Montage_IsPlaying(Attack))
			{
				// Run attack animation
				pAnimInst->Montage_Play(Attack);
			}
		}
	}


	// Finish execution
	FinishLatentTask(a_pTreeComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
