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

void UStaff::GetNotification(const FString& InSchool, const FString& InNewCourseInfo)
{
	UE_LOG(LogTemp, Log, TEXT("[UStaff] %s: %s"), *InSchool, *InNewCourseInfo);
}
