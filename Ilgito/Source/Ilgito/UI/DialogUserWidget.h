// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ILGITO_API UDialogUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UDialogUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCanvasPanel> RootCanvas;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> Image;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> Image2;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> NameText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> ScriptText;

};
