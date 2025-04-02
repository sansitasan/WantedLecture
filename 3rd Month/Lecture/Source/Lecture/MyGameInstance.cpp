// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Person.h"
#include "MyObject.h"

UMyGameInstance::UMyGameInstance()
{
	//CDO °´Ã¼¿¡ µé¾î°¨
	//ÅÛÇÃ¸´ Å¬·¡½º °´Ã¼·Î »ý¼ºÀÌ µÊ
	SchoolName = TEXT("WantedSchool");
}

void UMyGameInstance::Init()
{
	// Call Parent Class's Function.
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("==========================="));

	UClass* RuntimeClass = GetClass();
	UClass* StaticClass = UMyGameInstance::StaticClass();
	//Assert
	//check(RuntimeClass == StaticClass);
	UE_LOG(LogTemp, Log, TEXT("School Class Name: %s"),
		*RuntimeClass->GetName());

	SchoolName = TEXT("Change Name");

	UE_LOG(LogTemp, Log, TEXT("Schools Name: %s"),
		*SchoolName);
	UE_LOG(LogTemp, Log, TEXT("School Default Name: %s"),
		*RuntimeClass->GetDefaultObject<UMyGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("==========================="));

	UPerson* Person = NewObject<UPerson>();
	UMyObject* Obj = NewObject<UMyObject>();
	Person->SetName(TEXT("Person1"));
	UE_LOG(LogTemp, Log, TEXT("New Person Name: %s"), *Person->GetName());

	FProperty* NameProperty = UPerson::StaticClass()->FindPropertyByName(TEXT("Name"));

	FString CurrentPersonName;
	if (NameProperty) {
		NameProperty->GetValue_InContainer(Person, &CurrentPersonName);
		UE_LOG(LogTemp, Log, TEXT("Current Person Name: %s"), *CurrentPersonName);

		FString NewPersonName(TEXT("SAM"));
		NameProperty->SetValue_InContainer(Person, &NewPersonName);
		UE_LOG(LogTemp, Log, TEXT("Change Person Name: %s"), *Person->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("==========================="));



	UFunction* DoLessonFunction = Person->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunction) {
		Person->ProcessEvent(DoLessonFunction, nullptr);
	}
}
