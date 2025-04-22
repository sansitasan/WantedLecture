// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HStageGimmick.generated.h"

DECLARE_DELEGATE(FOnStageChangedDelegate);

USTRUCT()
struct FOnStageChangedDelegateWrapper {
	GENERATED_BODY()

	FOnStageChangedDelegateWrapper() {}
	explicit FOnStageChangedDelegateWrapper(FOnStageChangedDelegate InStageChangedDelegate)
		: StageChangedDelegate(InStageChangedDelegate) {}

	FOnStageChangedDelegate StageChangedDelegate;
};

UENUM(BlueprintType)
enum class EStageState : uint8 {
	Ready,
	Fight,
	Reward,
	Next
};

UCLASS()
class ARENABATTLEDEMO_API AHStageGimmick : public AActor
{
	GENERATED_BODY()
	
public:	
	AHStageGimmick();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	
	UPROPERTY(VisibleAnywhere, Category = Stage, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Stage;

	UPROPERTY(VisibleAnywhere, Category = Stage, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> StageTrigger;

	UPROPERTY(EditAnywhere, Category = Stage, meta = (AllowPrivateAccess = "true"))
	EStageState CurrentState;

	void SetState(EStageState InNewState);

	UFUNCTION()
	void OnStageTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UPROPERTY(VisibleAnywhere, Category = Stage, meta = (AllowPrivateAccess = "true"))
	TMap<EStageState, FOnStageChangedDelegateWrapper> StageChangedActions;

	void SetReady();
	void SetFight();
	void SetChooseReward();
	void SetChooseNext();

protected:
	UPROPERTY(VisibleAnywhere, Category = Gate, meta = (AllowPrivateAccess = "true"))
	TMap<FName, TObjectPtr<class UStaticMeshComponent>> Gates;

	UPROPERTY(VisibleAnywhere, Category = Gate, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UBoxComponent>> GateTriggers;

	UFUNCTION()
	void OnGateTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void OpenAllGates();
	void CloseAllGates();

protected:
	UPROPERTY(EditAnywhere, Category = Fight, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACharacterNonPlayer> OpponentClass;

	UPROPERTY(EditAnywhere, Category = Fight, meta = (AllowPrivateAccess = "true"))
	float OpponentSpawnTime;

	UFUNCTION()
	void OpponentDestroyed(AActor* DestroyedActor);

	FTimerHandle OpponentTimerHandle;

	void OpponentSpawn();
};
