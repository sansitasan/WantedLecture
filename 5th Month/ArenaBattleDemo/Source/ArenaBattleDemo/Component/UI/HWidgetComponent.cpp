// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/HWidgetComponent.h"
#include "UI/HUserWidget.h"

void UHWidgetComponent::InitWidget()
{
	// create widget instance about widgetclass info when it call
	Super::InitWidget();

	UHUserWidget* UserWidget = Cast<UHUserWidget>(GetWidget());
	if (!UserWidget) return;
	UserWidget->SetOwningActor(GetOwner());
}
