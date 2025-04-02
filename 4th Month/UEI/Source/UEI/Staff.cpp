// Fill out your copyright notice in the Description page of Project Settings.


#include "Staff.h"
#include "Card.h"

UStaff::UStaff()
{
	Name = TEXT("BUBU");
	Card->SetCardType(ECardType::Staff);
}

void UStaff::DoLesson()
{
	UE_LOG(LogTemp, Log, TEXT("%s BIBI"), *Name);
}
