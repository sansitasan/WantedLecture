// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_AttackHitCheck.h"
#include "Interface/HAnimationAttackInterface.h"

UAnimNotify_AttackHitCheck::UAnimNotify_AttackHitCheck()
{

}

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp) return;
	IHAnimationAttackInterface* AttackInterface = Cast<IHAnimationAttackInterface>(MeshComp->GetOwner());

	if (!AttackInterface) return;
	AttackInterface->AttackHitCheck();
}
