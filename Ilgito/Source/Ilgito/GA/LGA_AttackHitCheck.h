// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LGA_AttackHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class ILGITO_API ULGA_AttackHitCheck : public UGameplayAbility
{
	GENERATED_BODY()

public:
	ULGA_AttackHitCheck();

	void ActivateAbility
	(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData
	) override;

protected:
	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
};
