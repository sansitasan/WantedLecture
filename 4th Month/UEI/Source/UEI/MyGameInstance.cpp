// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Person.h"
#include "MyObject.h"
#include "Staff.h"
#include "Card.h"

UMyGameInstance::UMyGameInstance()
{
	//CDO °´Ã¼¿¡ µé¾î°¨
	//ÅÛÇÃ¸´ Å¬·¡½º °´Ã¼·Î »ý¼ºÀÌ µÊ
	SchoolName = TEXT("WantedSchool");
}

void UMyGameInstance::Init()
{
	Super::Init();

	TArray<UPerson*> Persons =
	{
		NewObject<UPerson>(),
		NewObject<UStaff>(),
		NewObject<UMyObject>()
	};

	for (const auto Person : Persons) {
		IITest* Interface = Cast<IITest>(Person);
		if (Interface) {
			Interface->DoLesson();
		}

		const UCard* OwnCard = Person->GetCard();
		ensure(OwnCard);

		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/UEI.ECardType"));

		if (CardEnumType) {
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue(
				(int64)OwnCard->GetCardType()).ToString();

			UE_LOG(LogTemp, Log, TEXT("%s's Card Type: %s"), *Person->GetName(), *CardMetaData);
		}
	}
}
