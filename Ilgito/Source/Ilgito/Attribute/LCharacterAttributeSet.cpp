// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/LCharacterAttributeSet.h"

ULCharacterAttributeSet::ULCharacterAttributeSet()
	: AttackRange(100.f), MaxAttackRange(300.f), AttackRadius(50.f), MaxAttackRadius(150.f), MaxHealth(100.f)
{
	InitHealth(GetMaxHealth());
}

void ULCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void ULCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
}
