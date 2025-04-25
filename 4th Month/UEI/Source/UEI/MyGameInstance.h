// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MyGameInstance.generated.h"

USTRUCT()
struct FStudentData {
	GENERATED_BODY()

	FStudentData()
		: Order(-1), Name(TEXT("Annie")) { }

	FStudentData(int32 InOrder, FString InName)
		: Order(InOrder), Name(InName) { }

	bool operator==(const FStudentData& InOther) const {
		return Order == InOther.Order;
	}

	friend FORCEINLINE int32 GetTypeHash(const FStudentData& InStudentData) {
		return GetTypeHash(InStudentData.Name);
	}

	friend FArchive& operator<<(FArchive& Archive, FStudentData& InStudentData) {
		Archive << InStudentData.Order;
		Archive << InStudentData.Name;
		return Archive;
	}

	UPROPERTY()
	int32 Order = -1;
	UPROPERTY()
	FString Name;
};

/**
 * 
 */
UCLASS()
class UEI_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	virtual void Init() override;

	void SaveStudentPackage();

	void LoadStudentPackage();

private:
	UPROPERTY()
	FString SchoolName;

	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;

	TArray<FStudentData> StudentData;

	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;

	TMap<int32, FString> StudentMap;

	UPROPERTY()
	TObjectPtr<class UStudent> StudentSource;

	//asset loading manager
	FStreamableManager StreamableManager;

	//asset loading manager handle
	TSharedPtr<FStreamableHandle> StreamableHandle;
};
