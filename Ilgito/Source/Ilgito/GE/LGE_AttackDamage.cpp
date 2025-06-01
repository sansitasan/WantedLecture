// Fill out your copyright notice in the Description page of Project Settings.


#include "GE/LGE_AttackDamage.h"
#include "Attribute/LCharacterAttributeSet.h"

ULGE_AttackDamage::ULGE_AttackDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	FGameplayModifierInfo HealthInfo;
	HealthInfo.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(ULCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(ULCharacterAttributeSet, Health)));
	HealthInfo.ModifierOp = EGameplayModOp::Additive;

	FScalableFloat DamageAmount(-30.f);
	FGameplayEffectModifierMagnitude ModMagnitude(DamageAmount);
	HealthInfo.ModifierMagnitude = ModMagnitude;

	Modifiers.Add(HealthInfo);
}
