// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogUserWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class UImage;
class UButton;
class UCanvasPanel;
enum class EDialogState : uint8;

UCLASS()
class ILGITO_API UDialogUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UDialogUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
    virtual void NativePreConstruct() override;

protected:
    void SendState(EDialogState DialogState);

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCanvasPanel> RootCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Image;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Image2;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> NameText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ScriptText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> LogButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> SkipButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ViewButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> AutoButton;
};
