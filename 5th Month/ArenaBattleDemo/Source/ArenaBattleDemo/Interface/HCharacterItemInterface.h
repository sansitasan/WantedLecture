// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HCharacterItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHCharacterItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARENABATTLEDEMO_API IHCharacterItemInterface
{
	GENERATED_BODY()

public:
	virtual void TakeItem(class UHItemData* InItemData) = 0;
};
