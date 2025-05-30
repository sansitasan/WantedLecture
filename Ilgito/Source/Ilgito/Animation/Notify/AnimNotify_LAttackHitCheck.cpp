// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_LAttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"

UAnimNotify_LAttackHitCheck::UAnimNotify_LAttackHitCheck()
{
}

FString UAnimNotify_LAttackHitCheck::GetNotifyName_Implementation() const
{
	return TEXT("LAttackHit");
}

void UAnimNotify_LAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(
		MeshComp, 
		Animation,
		EventReference
		);

	if (!MeshComp) return;
	
	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor) return;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		OwnerActor, 
		TriggerGameplayTag,
		FGameplayEventData()
		);
}
