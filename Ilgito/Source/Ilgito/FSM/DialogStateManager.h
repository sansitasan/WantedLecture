// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogStateManager.generated.h"

/**
 * 
 */

enum class EDialogState : uint8;
class UDialogState;
class UDialogModel;

UCLASS(Blueprintable, BlueprintType)
class ILGITO_API UDialogStateManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool SetState(EDialogState NewState);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDialogModel> DialogModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDialogState> CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EDialogState, TObjectPtr<UDialogState>> StateMap;
};