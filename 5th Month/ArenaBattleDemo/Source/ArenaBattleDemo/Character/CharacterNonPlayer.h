// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/CharacterBase.h"
#include "CharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEDEMO_API ACharacterNonPlayer : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	ACharacterNonPlayer();

protected:
	virtual void SetDead() override;
};
