// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Data/HCharacterStatComponent.h"
#include "Data/HGameSingleton.h"

UHCharacterStatComponent::UHCharacterStatComponent()
{
	//CurrentHp = MaxHp;
	CurrentLevel = 1.f;
}

void UHCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	SetLevel(static_cast<int32>(CurrentLevel));

	SetHp(BaseStat.MaxHp);
}

void UHCharacterStatComponent::SetLevel(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UHGameSingleton::Get().CharacterMaxLevel);

	BaseStat = UHGameSingleton::Get().GetCharacterStat(CurrentLevel);

	check(BaseStat.MaxHp > 0.f);
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
	CurrentHp = FMath::Clamp<float>(NewHp, 0.f, BaseStat.MaxHp);
	OnHpChanged.Broadcast(CurrentHp);
}
