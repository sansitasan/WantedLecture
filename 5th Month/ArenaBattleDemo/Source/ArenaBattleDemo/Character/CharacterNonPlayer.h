// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/CharacterBase.h"
#include "Interface/HCharacterAIInterface.h"
#include "Engine/StreamableManager.h"
#include "CharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS(config=ArenaBattle)
class ARENABATTLEDEMO_API ACharacterNonPlayer : public ACharacterBase, public IHCharacterAIInterface
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

protected:
	float GetAIPatrolRadius() override;
	float GetAIDetectRange() override;
	float GetAIAttackRange() override;
	float GetAITurnSpeed() override;

	void AttackByAI() override;
	void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;

	virtual void NotifyComboActionEnd() override;

	FAICharacterAttackFinished OnAttackFinished;
};
