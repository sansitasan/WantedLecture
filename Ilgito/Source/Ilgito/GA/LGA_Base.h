// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LGA_Base.generated.h"

/**
 * 
 */
UCLASS()
class ILGITO_API ULGA_Base : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	ULGA_Base();

	virtual void CancelAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateCancelAbility) override;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData);
};
