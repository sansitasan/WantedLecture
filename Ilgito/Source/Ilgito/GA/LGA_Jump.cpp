// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/LGA_Jump.h"
#include "GameFramework/Character.h"
#include "GA/AT/LAT_HumpAndWaitForLanding.h"

ULGA_Jump::ULGA_Jump()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULGA_Jump::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(
		Handle,
		ActorInfo,
		ActivationInfo,
		TriggerEventData
	);

	ULAT_HumpAndWaitForLanding* HumpAndWaitForLandingTask = ULAT_HumpAndWaitForLanding::CreateTask(this);

	HumpAndWaitForLandingTask->ReadyForActivation();
	HumpAndWaitForLandingTask->OnComplete.AddDynamic(this, &ULGA_Jump::OnLandedCallback);
}

bool ULGA_Jump::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayTagContainer* SourceTags, 
	const FGameplayTagContainer* TargetTags, 
	OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(
		Handle, 
		ActorInfo, 
		SourceTags, 
		TargetTags, 
		OptionalRelevantTags
	);

	if (!bResult) return false;

	const ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());

	return Character && Character->CanJump();
}

void ULGA_Jump::InputReleased(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	Character->StopJumping();
}

void ULGA_Jump::OnLandedCallback()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
