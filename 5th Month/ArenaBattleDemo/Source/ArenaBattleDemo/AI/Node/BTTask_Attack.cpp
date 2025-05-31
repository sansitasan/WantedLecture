// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/BTTask_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Interface/HCharacterAIInterface.h"

UBTTask_Attack::UBTTask_Attack()
{
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControllingPawn) return EBTNodeResult::Failed;

	IHCharacterAIInterface* AIPawn = Cast<IHCharacterAIInterface>(ControllingPawn);
	if (!AIPawn) return EBTNodeResult::Failed;

	FAICharacterAttackFinished OnAttackfinished;
	
	OnAttackfinished.BindLambda(
		[&]() {
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	AIPawn->SetAIAttackDelegate(OnAttackfinished);

	AIPawn->AttackByAI();
	return EBTNodeResult::InProgress;
}
