// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

UENUM()
enum class ECardType : uint8
{
	Person = 1 UMETA(DisplayName = "For Person"),
	MyObject = 2 UMETA(DisplayName = "For MyObject"),
	Staff = 4 UMETA(DisplayName = "For Staff"),
	InValid = 0xff
};

/**
 * 
 */
UCLASS()
class UEI_API UCard : public UObject
{
	GENERATED_BODY()
	
public:
	UCard();

	ECardType GetCardType() const;
	void  SetCardType(ECardType InCardType);

private:
	UPROPERTY()
	ECardType CardType;

	UPROPERTY()
	int32 Id;
};
