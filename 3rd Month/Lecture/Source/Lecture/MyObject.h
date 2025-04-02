// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilitySystemInterface.h"
#include "Person.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API UMyObject : public UPerson, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:

	UMyObject();

	virtual void DoLesson() override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY()
	int32 Id;

	UPROPERTY(EditAnywhere, Category=GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

};
