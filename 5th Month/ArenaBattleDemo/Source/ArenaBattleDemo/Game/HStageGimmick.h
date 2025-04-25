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
	Ready UMETA(DisplayName = "Ready"),
	Fight UMETA(DisplayName = "Fight"),
	Reward UMETA(DisplayName = "Reward"),
	Next UMETA(DisplayName = "Next")
};

UCLASS()
class ARENABATTLEDEMO_API AHStageGimmick : public AActor
{
	GENERATED_BODY()
	
public:	
	AHStageGimmick();

	virtual void OnConstruction(const FTransform& Transform) override;

	FORCEINLINE int32 GettageNum() const { return CurrentStageNum; }
	FORCEINLINE void SetStageNum(int32 InNewStageNum) 
	{
		CurrentStageNum = InNewStageNum;
	}

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

protected:
	UPROPERTY(VisibleAnywhere, Category = Reward, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AHItemBox> RewardItemClass;

	//보상 상자는 스테이지와 무관하기에 강참조보다는 약참조가 좋다.
	UPROPERTY(VisibleAnywhere, Category = Reward, meta = (AllowPrivateAccess = "true"))
	TArray<TWeakObjectPtr<class AHItemBox>> RewardBoxes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Reward, meta = (AllowPrivateAccess = "true"))
	TMap<FName, FVector> RewardBoxLocations;

	UFUNCTION()
	void OnReawrdTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void SpawnRewardBoxes();

protected:
	UPROPERTY(VisibleInstanceOnly, Category = Reward, meta = (AllowPrivateAccess = "true"))
	int32 CurrentStageNum;
};
