// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HadesPlayerController.h"

void AHadesPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//���� �� ���콺�� ����Ʈ�� �ԷµǾ� �ٷ� ����
	FInputModeGameOnly GameInput;

	SetInputMode(GameInput);
}
