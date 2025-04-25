// Fill out your copyright notice in the Description page of Project Settings.


#include "HadesGameMode.h"

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
}
