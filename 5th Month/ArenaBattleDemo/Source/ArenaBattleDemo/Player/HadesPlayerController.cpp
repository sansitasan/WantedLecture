// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HadesPlayerController.h"

AHadesPlayerController::AHadesPlayerController()
{

}

void AHadesPlayerController::GameScoreChanged(int32 NewScore)
{
	K2_OnScoreChanged(NewScore);
}

void AHadesPlayerController::GameClear()
{
	K2_OnGameClear();
}

void AHadesPlayerController::GameOver()
{
	K2_OnGameOver();
}

void AHadesPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//���� �� ���콺�� ����Ʈ�� �ԷµǾ� �ٷ� ����
	FInputModeGameOnly GameInput;

	SetInputMode(GameInput);
}
