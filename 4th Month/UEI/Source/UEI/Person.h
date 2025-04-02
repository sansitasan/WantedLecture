// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

class UCard;

/**
 * 
 */
UCLASS()
class UEI_API UPerson : public UObject
{
	GENERATED_BODY()
public:
	UPerson();

	const FString& GetName() const;
	void SetName(const FString& InName);

	UCard* GetCard() const;
	void SetCard(UCard* InCard);

protected:
	UPROPERTY()
	TObjectPtr<UCard> Card;

	UPROPERTY()
	FString Name;
};
