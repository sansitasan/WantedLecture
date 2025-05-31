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
	//시작 시 마우스가 뷰포트로 입력되어 바로 실행
	FInputModeGameOnly GameInput;

	SetInputMode(GameInput);
}
