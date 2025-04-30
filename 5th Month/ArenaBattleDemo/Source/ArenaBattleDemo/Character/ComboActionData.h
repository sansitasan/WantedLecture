// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEDEMO_API UComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UComboActionData();

public:
	//��Ÿ�� ���� �̸� ���λ� (ComboAttack)
	UPROPERTY(EditAnywhere, Category = Name)
	FString MontageSectionNamePrefix;

	UPROPERTY(EditAnywhere, Category = ComboData)
	uint8 MaxComboCount;

	UPROPERTY(EditAnywhere, Category = ComboData)
	float FrameRate;

	UPROPERTY(EditAnywhere, Category = ComboData)
	TArray<float> EffectiveFrameCount;
};
