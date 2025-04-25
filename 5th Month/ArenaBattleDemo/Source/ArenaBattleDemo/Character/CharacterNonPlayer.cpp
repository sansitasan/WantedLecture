// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterNonPlayer.h"
#include "AI/HAIController.h"
#include "Engine/AssetManager.h"

ACharacterNonPlayer::ACharacterNonPlayer()
{
	GetMesh()->SetHiddenInGame(true);

	AIControllerClass = AHAIController::StaticClass();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ACharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ensure(NPCMeshes.Num() > 0);

	int32 RandomIndex = FMath::RandRange(0, NPCMeshes.Num() - 1);
	NPCMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad
	(
		NPCMeshes[RandomIndex],
		FStreamableDelegate::CreateUObject
		(
			this,
			&ACharacterNonPlayer::NPCMeshSet
		)
	);
}

void ACharacterNonPlayer::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		DeadTimerHandle, 
		FTimerDelegate::CreateLambda([&]() 
			{
				Destroy();
			}
		), 
		3.f, 
		false);
}

void ACharacterNonPlayer::NPCMeshSet()
{
	NPCMeshLoadCompleted();
	NPCMeshHandle->ReleaseHandle();
}

void ACharacterNonPlayer::NPCMeshLoadCompleted()
{
	if (!NPCMeshHandle.IsValid()) return;
	USkeletalMesh* NPCMesh = Cast<USkeletalMesh>(NPCMeshHandle->GetLoadedAsset());

	if (!NPCMesh) return;
	GetMesh()->SetSkeletalMesh(NPCMesh);
	GetMesh()->SetHiddenInGame(false);
}
