// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/HCharacterStat.h"
#include "HCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENABATTLEDEMO_API UHCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	FORCEINLINE float GetMaxHP() const { return BaseStat.MaxHp + ModifierStat.MaxHp; }
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }

	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	void SetLevel(int32 InNewLevel);

	FORCEINLINE void SetModifierStat(const FHCharacterStat& InModifierStat) 
	{
		ModifierStat = InModifierStat;
	}

	FORCEINLINE FHCharacterStat GetTotalStat() const
	{
		return BaseStat + ModifierStat;
	}
	

	float ApplyDamaage(float InDamage);

protected:
	void SetHp(float NewHp);

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
		
protected:
	//Transient = 현재 체력 값은 게임을 진행할 때마다 바뀐다.
	//따라서 디스크에 명시적으로 저장할 필요가 없을 수 있다.
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float CurrentLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FHCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FHCharacterStat ModifierStat;
};
