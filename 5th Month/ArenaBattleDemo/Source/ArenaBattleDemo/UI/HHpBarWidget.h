// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUserWidget.h"
#include "HHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEDEMO_API UHHpBarWidget : public UHUserWidget
{
	GENERATED_BODY()

public:
	UHHpBarWidget(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }

	void UpdateHpBar(float NewCurrentHp);

protected:
	//call when UMG Initialize
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
};
