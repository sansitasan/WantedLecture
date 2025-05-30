// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Attribute/LCharacterAttributeSet.h"

ALPlayerState::ALPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
	AttributeSet = CreateDefaultSubobject<ULCharacterAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ALPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
