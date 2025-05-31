// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "LCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//ATTRIBUTE_ACCESSORS(UMyHealthSet, Health)

/**
 * 
 */
UCLASS()
class ILGITO_API ULCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ULCharacterAttributeSet();

	ATTRIBUTE_ACCESSORS(ULCharacterAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS(ULCharacterAttributeSet, AttackRange);

	ATTRIBUTE_ACCESSORS(ULCharacterAttributeSet, MaxAttackRadius);
	ATTRIBUTE_ACCESSORS(ULCharacterAttributeSet, AttackRadius);
	
	ATTRIBUTE_ACCESSORS(ULCharacterAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(ULCharacterAttributeSet, AttackRate);

	ATTRIBUTE_ACCESSORS(ULCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(ULCharacterAttributeSet, Health);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRange;

	UPROPERTY(BlueprintReadOnly, Category="Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
};
