// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "HAI.h"

AHAIController::AHAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/ArenaBattle/AI/BB_HCharacter.BB_HCharacter"));
	if (BBAssetRef.Object) {
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/ArenaBattle/AI/BT_HCharacter.BT_HCharacter"));
	if (BTAssetRef.Object) {
		BTAsset = BTAssetRef.Object;
	}
}

void AHAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	ensure(UseBlackboard(BBAsset, BlackboardPtr));
	Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());
	ensure(RunBehaviorTree(BTAsset));
}

void AHAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (!BTComponent) return;
	BTComponent->StopTree();
}

void AHAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}
