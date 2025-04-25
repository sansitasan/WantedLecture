// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"

UPerson::UPerson()
{
	Name = TEXT("San Kim");
	Year = 28;
}

void UPerson::DoLesson()
{
	UE_LOG(LogTemp, Log, TEXT("%s is in Lesson"), *Name);
}

const FString& UPerson::GetName() const
{
	return Name;
}

void UPerson::SetName(const FString& InName)
{
	Name = InName;
}
