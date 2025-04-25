// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.h"
#include "ITest.h"
#include "Staff.generated.h"

/**
 * 
 */
UCLASS()
class UEI_API UStaff : public UPerson, public IITest
{
	GENERATED_BODY()
	
public:
	UStaff();

	virtual void DoLesson() override;

	void GetNotification(const FString& InSchool, const FString& InNewCourseInfo);
};
