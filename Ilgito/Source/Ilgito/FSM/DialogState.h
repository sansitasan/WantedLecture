// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogState.generated.h"

UENUM(Blueprintable, BlueprintType)
enum class EDialogState : uint8
{
	None				UMETA(DisplayName = "None"),
	Auto				UMETA(DisplayName = "Auto"),
	WaitInput			UMETA(DisplayName = "WaitInput"),
	Choice				UMETA(DisplayName = "Choice"),
	Log					UMETA(DisplayName = "Log"),
	Undo				UMETA(DisplayName = "Undo"),
	View				UMETA(DisplayName = "View"),
	Skip				UMETA(DisplayName = "Skip")
};
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class ILGITO_API UDialogState : public UObject
{
	GENERATED_BODY()
	
public:
	UDialogState();

	virtual void Enter() { UE_LOG(LogTemp, Log, TEXT("Enter Dialog %s State"), *StaticEnum<EDialogState>()->GetDisplayNameTextByValue(static_cast<int64>(State)).ToString()); }
	virtual void Update() { UE_LOG(LogTemp, Log, TEXT("Update Dialog %s State"), *StaticEnum<EDialogState>()->GetDisplayNameTextByValue(static_cast<int64>(State)).ToString()); }
	virtual void Exit() { UE_LOG(LogTemp, Log, TEXT("Exit Dialog %s State"), *StaticEnum<EDialogState>()->GetDisplayNameTextByValue(static_cast<int64>(State)).ToString()); }

	FORCEINLINE void SetState(EDialogState InState) { State = InState; }
	FORCEINLINE EDialogState GetState() { return State; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EDialogState State;
};