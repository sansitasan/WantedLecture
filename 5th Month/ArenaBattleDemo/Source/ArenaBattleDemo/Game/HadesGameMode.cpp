// Fill out your copyright notice in the Description page of Project Settings.


#include "HadesGameMode.h"
#include "Player/HadesPlayerController.h"

AHadesGameMode::AHadesGameMode()
{
	//static ConstructorHelpers::FClassFinder<APawn> ThirdPersonCharacterRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	static ConstructorHelpers::FClassFinder<APawn> DefaultCharacterRef(TEXT("/Script/ArenaBattleDemo.CharacterPlayer"));
	if (DefaultCharacterRef.Class) {
		DefaultPawnClass = DefaultCharacterRef.Class;
	}

	//Same about under
	// #include "Player/HadesPlayerController.h"를 없앨 수 있음
	//PlayerControllerClass = AHadesPlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ArenaBattleDemo.HadesPlayerController"));

	if (PlayerControllerClassRef.Class) {
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	ClearScore = 3;
	CurrentScore = 0;
	bIsCleared = false;
}

void AHadesGameMode::OnPlayerScoreChanged(int32 NewPlayerScore)
{
	CurrentScore = NewPlayerScore;

	AHadesPlayerController* PlayerController = Cast<AHadesPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController) return;
	PlayerController->GameScoreChanged(CurrentScore);

	if (CurrentScore >= ClearScore)
	{
		bIsCleared = true;
		PlayerController->GameClear();
	}
}

void AHadesGameMode::OnPlayerDead()
{
	ResetLevel();

	AHadesPlayerController* PlayerController = Cast<AHadesPlayerController>(GetWorld()->GetFirstPlayerController());

	if (PlayerController) {
		PlayerController->GameOver();
	}
}

bool AHadesGameMode::IsGameCleared()
{
	return bIsCleared;
}
