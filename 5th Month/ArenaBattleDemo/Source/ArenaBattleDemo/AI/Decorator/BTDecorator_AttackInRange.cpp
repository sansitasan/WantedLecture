// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTDecorator_AttackInRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Interface/HCharacterAIInterface.h"
#include "AI/HAI.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControllingPawn) return false;

	IHCharacterAIInterface* AIPawn = Cast<IHCharacterAIInterface>(ControllingPawn);
	if (!AIPawn) return false;

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (!Target) return false;

	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);

	return AttackRangeWithRadius >= DistanceToTarget;
}
