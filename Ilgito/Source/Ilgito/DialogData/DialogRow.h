#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogRow.generated.h"

UENUM(BlueprintType)
enum class EDialogType : uint8
{
	Dialog,
	Choice
};

USTRUCT(BlueprintType)
struct FDialogRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Script)
	EDialogType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Script)
	FName SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Script)
	FString DialogText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Script)
	TArray<FName> ChildIDs;
};
