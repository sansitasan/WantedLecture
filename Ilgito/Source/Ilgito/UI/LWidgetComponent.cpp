// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LWidgetComponent.h"
#include "UI/LUserWidget.h"

void ULWidgetComponent::InitWidget()
{
	Super::InitWidget();
	ULUserWidget* UserWidget = Cast<ULUserWidget>(GetWidget());
	if (!UserWidget) return;
}
