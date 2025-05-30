// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "LTA_Trace.generated.h"

/**
 * 
 */
UCLASS()
class ILGITO_API ALTA_Trace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	ALTA_Trace();

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual bool IsConfirmTargetingAllowed() override;

	virtual void ConfirmTargetingAndContinue() override;

	FORCEINLINE void SetShowDebug(bool InShowDebug) { bShowDebug = InShowDebug; }

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const;

	bool bShowDebug = false;
};
