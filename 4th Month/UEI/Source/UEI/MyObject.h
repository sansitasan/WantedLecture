// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.h"
#include "ITest.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS()
class UEI_API UMyObject : public UPerson, public IITest
{
	GENERATED_BODY()
	
public:

	UMyObject();

	virtual void DoLesson() override;
};
