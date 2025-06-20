// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogUserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "FSM/DialogState.h"
#include "Blueprint/WidgetTree.h"

UDialogUserWidget::UDialogUserWidget(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	

}

void UDialogUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDialogUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

#if WITH_EDITOR
	if (IsDesignTime())
	{
		if (ScriptText)
		{
			ScriptText->SetText(FText::FromString(TEXT("Test Dialog")));
		}
		if (NameText)
		{
			NameText->SetText(FText::FromString(TEXT("NPC")));
		}
	}
#endif
}

void UDialogUserWidget::SendState(EDialogState DialogState)
{

}
