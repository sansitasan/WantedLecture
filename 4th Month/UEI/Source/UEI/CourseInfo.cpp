// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseInfo.h"

UCourseInfo::UCourseInfo()
{
	Contents = TEXT("Default Course Info");
}

void UCourseInfo::ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents)
{
	Contents = InNewContents;

	UE_LOG(LogTemp, Log, TEXT("[CourseInfo] ChangedCourseInfo"));
	OnChanged.Execute(InSchoolName, InNewContents);//Broadcast(InSchoolName, InNewContents);
}
