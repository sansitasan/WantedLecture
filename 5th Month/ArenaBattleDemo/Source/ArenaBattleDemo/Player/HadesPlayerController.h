// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HadesPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEDEMO_API AHadesPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AHadesPlayerController();

	//블루프린트에 이벤트를 발생시켜주는 함수
	//블루프린트에서 만들어진 함수를 cpp에서 호출함
	//K2는 관성적으로 붙이는 이름. Kismet
	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "OnScoreChangedCpp"))
	void K2_OnScoreChanged(int32 NewScore);

	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "OnGameClearCpp"))
	void K2_OnGameClear();

	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "K2_OnGameOverCpp"))
	void K2_OnGameOver();

	void GameScoreChanged(int32 NewScore);
	void GameClear();
	void GameOver();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveGame)
	TObjectPtr<class UHSaveGame> SaveGameInstance;
};
