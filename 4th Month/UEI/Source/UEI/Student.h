// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class UEI_API UStudent : public UObject
{
	GENERATED_BODY()
	
public:
	UStudent();

	virtual void Serialize(FArchive& Ar) override;

	inline int32 GetOrder() const { return Order; }
	inline void SetOrder(int32 InOrder) { Order = InOrder; }

	inline FString GetName() const { return Name; }
	inline void SetName(const FString& InName) { Name = InName; }

private:
	UPROPERTY(VisibleAnywhere)
	int32 Order;

	UPROPERTY(VisibleAnywhere)
	FString Name;
};
