// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_Detect.h"
#include "AIController.h"
#include "Physics/HCollision.h"
#include "Interface/HCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/HAI.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.f;
	bNotifyTick = true;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	IHCharacterAIInterface* AIPawn = Cast<IHCharacterAIInterface>(ControllingPawn);
	if (!AIPawn) return;

	TArray<FOverlapResult> OverlapResults;
	FVector Center = ControllingPawn->GetActorLocation();
	FCollisionQueryParams CollisionQueryParams
	(
		SCENE_QUERY_STAT(Detect),
		false,
		ControllingPawn
	);

	float DetectRange = AIPawn->GetAIDetectRange();

	bool bOverlapped = World->OverlapMultiByChannel
	(
		OverlapResults,
		Center,
		FQuat::Identity,
		CCHANNEL_HACTION,
		FCollisionShape::MakeSphere(DetectRange),
		CollisionQueryParams
	);

	if (!bOverlapped) 
	{ 
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
		return; 
	}

	for (auto const& OverlapResult : OverlapResults) 
	{
		APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());

		if (!Pawn || !Pawn->GetController()->IsPlayerController()) continue;
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
		DrawDebugSphere
		(
			World,
			Center,
			DetectRange,
			16,
			FColor::Green,
			false,
			0.2f
		);

		DrawDebugPoint
		(
			World,
			Pawn->GetActorLocation(),
			10.f,
			FColor::Green,
			false,
			0.2f
		);

		DrawDebugLine
		(
			World,
			ControllingPawn->GetActorLocation(),
			Pawn->GetActorLocation(),
			FColor::Green,
			false,
			0.2f
		);

		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);

	DrawDebugSphere
	(
		World,
		Center,
		DetectRange,
		16,
		FColor::Red,
		false,
		0.2f
	);
}
