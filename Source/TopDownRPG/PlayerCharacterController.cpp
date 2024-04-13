// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacterController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacterController::APlayerCharacterController(FObjectInitializer const& a_pObjectInit)
{
	// Init the tree and blackboard components
	m_pBehaviorTreeComponent = a_pObjectInit.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTree Component"));
	m_pBlackboard = a_pObjectInit.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("Blackboard Component"));
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	// Run the behavior tree
	RunBehaviorTree(m_pBehaviorTree);
	m_pBehaviorTreeComponent->StartTree(*m_pBehaviorTree);
}

void APlayerCharacterController::OnPossess(APawn* a_pPawn)
{
	// Run default possess method
	Super::OnPossess(a_pPawn);

	// Init blackboard
	if (m_pBlackboard)
	{
		m_pBlackboard->InitializeBlackboard(*m_pBehaviorTree->BlackboardAsset);
	}
}

UBlackboardComponent* APlayerCharacterController::GetBlackboard() const
{
	return m_pBlackboard;
}