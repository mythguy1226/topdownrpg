// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_IsMemberInRange.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UBTS_IsMemberInRange::UBTS_IsMemberInRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Member In Range");
}

void UBTS_IsMemberInRange::OnBecomeRelevant(UBehaviorTreeComponent& a_pTreeComp, uint8* a_pNodeMem)
{
	// Super Call 
	Super::OnBecomeRelevant(a_pTreeComp, a_pNodeMem);

	// Get blackboard from ai controller
	UBlackboardComponent* pBlackboard = Cast<UBlackboardComponent>(a_pTreeComp.GetAIOwner()->GetComponentByClass(UBlackboardComponent::StaticClass()));

	// Get group member from the board
	AActor* pMember = Cast<AActor>(pBlackboard->GetValueAsObject(MemberBlackboardKey.SelectedKeyName));
	
	// Set blackboard key to whether or not member is in range
	if (pMember)
		pBlackboard->SetValueAsBool(GetSelectedBlackboardKey(), a_pTreeComp.GetAIOwner()->GetPawn()->GetDistanceTo(pMember) <= m_fRange);
}
