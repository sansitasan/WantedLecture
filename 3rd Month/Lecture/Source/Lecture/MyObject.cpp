// Fill out your copyright notice in the Description page of Project Settings.

#include "MyObject.h"
#include "AbilitySystemComponent.h"

UMyObject::UMyObject()
{
	Name = TEXT("UObject");
	Year = 0;
	Id = 1;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

void UMyObject::DoLesson()
{
	Super::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%d year Object %s is do lesson"), Year, *Name);
}

UAbilitySystemComponent* UMyObject::GetAbilitySystemComponent() const
{
	return ASC;
}
