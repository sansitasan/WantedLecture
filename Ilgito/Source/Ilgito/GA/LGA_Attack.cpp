// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/LGA_Attack.h"
#include "Character/LCharacterBase.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFrameWork/CharacterMovementComponent.h"
//#include "Animation/AnimMontage.h"

ULGA_Attack::ULGA_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(
		Handle, 
		ActorInfo, 
		ActivationInfo, 
		bReplicateCancelAbility
	);
}

void ULGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(
		Handle,
		ActorInfo,
		ActivationInfo,
		TriggerEventData
	);

	ALCharacterBase* LCharacter = CastChecked<ALCharacterBase>(ActorInfo->AvatarActor.Get());
	LCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	UAnimMontage* Test = CreateDefaultSubobject<UAnimMontage>(TEXT(""));
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), Test);
	PlayAttackTask->OnCompleted.AddDynamic(this, &ULGA_Attack::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &ULGA_Attack::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();
}

void ULGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(
		Handle,
		ActorInfo,
		ActivationInfo,
		bReplicateEndAbility,
		bWasCancelled
	);

	ALCharacterBase* LCharacter = CastChecked<ALCharacterBase>(ActorInfo->AvatarActor.Get());
	LCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ULGA_Attack::InputPressed(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	
}

void ULGA_Attack::OnCompleteCallback()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void ULGA_Attack::OnInterruptedCallback()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
