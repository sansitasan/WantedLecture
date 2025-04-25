// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HCharacterStat.h"
#include "HGameSingleton.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEDEMO_API UHGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UHGameSingleton();

	static UHGameSingleton& Get();

public:
	FORCEINLINE FHCharacterStat GetCharacterStat(int32 InLevel) const 
	{
		return CharacterStatTable.IsValidIndex(InLevel - 1) ? CharacterStatTable[InLevel - 1] : FHCharacterStat();
	}

	UPROPERTY()
	int32 CharacterMaxLevel;

private:
	TArray<FHCharacterStat> CharacterStatTable;
};
