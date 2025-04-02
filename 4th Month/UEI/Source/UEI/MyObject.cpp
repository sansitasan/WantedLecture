// Fill out your copyright notice in the Description page of Project Settings.

#include "MyObject.h"
#include "Card.h"

UMyObject::UMyObject()
{
	Name = TEXT("UObject");
	Card->SetCardType(ECardType::MyObject);
}

void UMyObject::DoLesson()
{
	//interface can't Super
	//IITest::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%s good"), *Name);
}
