// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTT_Attack::UBTT_Attack(FObjectInitializer const& a_pObjectInit)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem)
{
	// Get the owning pawn and its anim instance
	UAnimInstance* pAnimInst = Cast<USkeletalMeshComponent>(a_pTreeComp.GetAIOwner()->GetPawn()->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();

	// Check that anim instance is valid
	if(!pAnimInst)
		return EBTNodeResult::Failed;

	// Check if any previous attacks are finished
	if (!pAnimInst->Montage_IsPlaying(Attack))
	{
		// Get blackboard from ai controller
		UBlackboardComponent* pBlackboard = Cast<UBlackboardComponent>(a_pTreeComp.GetAIOwner()->GetComponentByClass(UBlackboardComponent::StaticClass()));

		// Get bool value from key to check whether we can attack
		bool bCanAttack = pBlackboard->GetValueAsBool(GetSelectedBlackboardKey());
		if (bCanAttack)
		{
			// Run attack animation
			pAnimInst->Montage_Play(Attack);
		}
	}

	// Finish execution
	FinishLatentTask(a_pTreeComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
