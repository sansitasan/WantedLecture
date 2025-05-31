// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/LGA_Base.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Tag/LGameplayTag.h"

ULGA_Base::ULGA_Base()
{
	AbilityTags.AddTag(LTAG_ACTOR_ROTATE);
	ActivationOwnedTags.AddTag(LTAG_ACTOR_ROTATING);
}

void ULGA_Base::CancelAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	AActor* Avatar = ActorInfo->AvatarActor.Get();
	//ActorInfo->OwnerActor.Get();

	if (!Avatar) return;
	URotatingMovementComponent* RotatingMovement = 
		Cast<URotatingMovementComponent>(
			Avatar->GetComponentByClass(URotatingMovementComponent::StaticClass()
			)
		);
	if (!RotatingMovement) return;
	RotatingMovement->Activate(true);

}

void ULGA_Base::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* Avatar = ActorInfo->AvatarActor.Get();

	if (!Avatar) return;
	URotatingMovementComponent* RotatingMovement =
		Cast<URotatingMovementComponent>(
			Avatar->GetComponentByClass(URotatingMovementComponent::StaticClass()
			)
		);
	if (!RotatingMovement) return;
	RotatingMovement->Deactivate();
}
