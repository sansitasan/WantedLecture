// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Data/HCharacterStatComponent.h"

UHCharacterStatComponent::UHCharacterStatComponent()
{
	MaxHp = 200.f;
	CurrentHp = MaxHp;
}

void UHCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHp(MaxHp);
}

float UHCharacterStatComponent::ApplyDamaage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamaage = FMath::Clamp<float>(InDamage, 0.f, InDamage);
	SetHp(PrevHp - ActualDamaage);

	if (CurrentHp <= KINDA_SMALL_NUMBER) {
		OnHpZero.Broadcast();
	}

	return ActualDamaage;
}

void UHCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.f, MaxHp);
	OnHpChanged.Broadcast(CurrentHp);
}
