// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LUserWidget.h"
#include "LUserHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class ILGITO_API ULUserHpBarWidget : public ULUserWidget
{
	GENERATED_BODY()
	
protected:

	float CurrentHp = 0.f;
	float CurrentMaxHp = 0.1f;
};
