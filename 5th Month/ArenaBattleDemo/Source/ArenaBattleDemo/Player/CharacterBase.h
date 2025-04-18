// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HAnimationAttackInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class ARENABATTLEDEMO_API ACharacterBase : public ACharacter, public IHAnimationAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AttackHitCheck() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	void ProcessComboCommand();

	void ComboActionBegin();

	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProerlyEnded);

	void SetComboCheckTimer();

	void ComboCheck();

protected:
	virtual void SetDead();

	void PlayDeadAnimation();

protected:
	//Attack Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	//Combo Data Asset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UComboActionData> ComboActionData;
	
	//Current Play Combo
	//0 = Combo is not Start, 1/2/3/4 = Combo Start
	int32 CurrentCombo = 0;
	
	//Combo Timer Handle
	FTimerHandle ComboTimerHandle;

	//내부에서만 쓰므로 uint8대신 bool을 씀
	bool HasNextComboCommand = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;
};
