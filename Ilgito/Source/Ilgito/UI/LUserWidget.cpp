// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LUserWidget.h"
#include "AbilitySystemBlueprintLibrary.h"

void ULUserWidget::SetAbilitySystemCompoenent(AActor* InOwner)
{
	if (!IsValid(InOwner)) return;
	ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwner);
}

UAbilitySystemComponent* ULUserWidget::GetAbilitySystemComponent() const
{
	return ASC;
}
