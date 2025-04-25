// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/CharacterBase.h"
#include "Engine/StreamableManager.h"
#include "CharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS(config=ArenaBattle)
class ARENABATTLEDEMO_API ACharacterNonPlayer : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	ACharacterNonPlayer();

protected:
	virtual void PostInitializeComponents() override;
	virtual void SetDead() override;

	void NPCMeshSet();
	void NPCMeshLoadCompleted();

	UPROPERTY(config)
	TArray<FSoftObjectPath> NPCMeshes;

	TSharedPtr<FStreamableHandle> NPCMeshHandle;
};
