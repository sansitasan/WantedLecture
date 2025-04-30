// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/BTTask_FindPatrolPos.h"
#include "AI/HAI.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Interface/HCharacterAIInterface.h"
#include "BehaviorTree/BlackBoardComponent.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControllingPawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (!NavSystem) return EBTNodeResult::Failed;

	IHCharacterAIInterface* AIPawn = Cast<IHCharacterAIInterface>(ControllingPawn);
	if (!AIPawn) return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);
	FNavLocation NextPatrolPos;
	if (!NavSystem->GetRandomPointInNavigableRadius(Origin, AIPawn->GetAIPatrolRadius(), NextPatrolPos))
		return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, NextPatrolPos);
	return EBTNodeResult::Succeeded;
}
