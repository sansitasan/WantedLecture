// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/HCharacterWidgetInterface.h"

UHHpBarWidget::UHHpBarWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxHp = -1.f;
}

void UHHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > .0f);

	if (!HpProgressBar) return;

	HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
}

void UHHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Pb_HpBar")));
	ensure(HpProgressBar);

	IHCharacterWidgetInterface* CharacterWidgetInterface = Cast<IHCharacterWidgetInterface>(OwningActor);
	if (!CharacterWidgetInterface) return;
	CharacterWidgetInterface->SetupCharacterWidget(this);
}
