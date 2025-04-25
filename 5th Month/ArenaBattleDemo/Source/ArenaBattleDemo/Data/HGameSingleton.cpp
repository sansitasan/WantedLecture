// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/HGameSingleton.h"

UHGameSingleton::UHGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Game/ArenaBattle/Data/HCharacterStat.HCharacterStat"));
	if (DataTableRef.Object) {
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;

		DataTable->GetRowMap().GenerateValueArray(ValueArray);

		Algo::Transform(ValueArray, CharacterStatTable, 
			[](uint8* Value)
			{
				return *reinterpret_cast<FHCharacterStat*>(Value);
			}
		);
	}

	CharacterMaxLevel = CharacterStatTable.Num();

	ensure(CharacterMaxLevel > 0);
}

UHGameSingleton& UHGameSingleton::Get()
{
	//Get Singleton
	//ProjectSetting - singleton
	static UHGameSingleton* Singleton = Cast<UHGameSingleton>(GEngine->GameSingleton);

	if (Singleton) return *Singleton;
	
	UE_LOG(LogTemp, Error, TEXT("Empty"));

	return *NewObject<UHGameSingleton>();
}
