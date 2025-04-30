// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/BTTask_TurnToTarget.h"
#include "BTTask_TurnToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/HAI.h"
#include "Interface/HCharacterAIInterface.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControllingPawn) return EBTNodeResult::Failed;

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (!TargetPawn) return EBTNodeResult::Failed;

	IHCharacterAIInterface* AIPawn = Cast<IHCharacterAIInterface>(TargetPawn);
	if (!AIPawn) return EBTNodeResult::Failed;

	float TurnSpeed = AIPawn->GetAITurnSpeed();

	FVector LookVector = TargetPawn->GetActorLocation() - ControllingPawn->GetActorLocation();
	LookVector.Z = 0.f;
	LookVector.Normalize();
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	FRotator CurrentRot = FMath::RInterpTo
	(
		ControllingPawn->GetActorRotation(),
		TargetRot,
		GetWorld()->DeltaTimeSeconds,
		TurnSpeed
	);

	ControllingPawn->SetActorRotation(CurrentRot);

	return EBTNodeResult::Succeeded;
}
