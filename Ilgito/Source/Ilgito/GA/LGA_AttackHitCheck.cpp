// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/LGA_AttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GA/AT/LAT_Trance.h"
#include "GA/TA/LTA_Trace.h"
#include "Attribute/LCharacterAttributeSet.h"

ULGA_AttackHitCheck::ULGA_AttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULGA_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(
		Handle,
		ActorInfo,
		ActivationInfo,
		TriggerEventData
	);

	ULAT_Trance* AttackTraceTask = ULAT_Trance::CreateTask(this, ULAT_Trance::StaticClass());
	AttackTraceTask->OnComplete.AddDynamic(this, &ULGA_AttackHitCheck::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();

}

void ULGA_AttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0)) 
	{
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		
		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
		//UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
		//if (!SourceASC || !TargetASC) return;
		//
		const ULCharacterAttributeSet* SourceAttribute = SourceASC->GetSet<ULCharacterAttributeSet>();
		//ULCharacterAttributeSet* TargetAttribute =
		//	const_cast<ULCharacterAttributeSet*>(
		//		TargetASC->GetSet<ULCharacterAttributeSet>()
		//		);
		//
		//if (!SourceAttribute || !TargetAttribute) return;
		//
		//const float AttackDamage = SourceAttribute->GetAttackRate();
		//TargetAttribute->SetHealth(TargetAttribute->GetHealth() - AttackDamage);

		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
		if (SpecHandle.IsValid()) return;

		//SpecHandle.Data->SetSetByCallerMagnitude(Tag, SourceAttribute->GetAttackRate());

		ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle, TargetDataHandle);
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}