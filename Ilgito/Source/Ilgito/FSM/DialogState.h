// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogState.generated.h"

UENUM()
enum class EDialogState : uint8
{
	None,
	Auto,
	WaitInput,
	Choice,
	Log,
	Undo,
	View,
	Skip
};
/**
 * 
 */
UCLASS(Blueprintable)
class ILGITO_API UDialogState : public UObject
{
	GENERATED_BODY()
	
public:
	UDialogState();

	virtual void Enter() {};
	virtual void Update() {};
	virtual void Exit() {};

	FORCEINLINE EDialogState GetState() { return State; }

private:
	EDialogState State;
};