// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/LCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

ULCharacterAttributeSet::ULCharacterAttributeSet()
	: AttackRange(100.f), MaxAttackRange(300.f), AttackRadius(50.f), MaxAttackRadius(150.f), MaxHealth(100.f), Damage(0.f)
{
	InitHealth(GetMaxHealth());
}

void ULCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetDamageAttribute())
	{
		NewValue = NewValue < 0.f ? 0.f : NewValue;
	}
}

void ULCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
}

bool ULCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return true;
}

void ULCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) 
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), 0.f, GetMaxHealth()));
	}
}
