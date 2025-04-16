// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/ComboActionData.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::ProcessComboCommand()
{
	//Combo Check
	if (CurrentCombo == 0) {
		ComboActionBegin();
		return;
	}

	HasNextComboCommand = ComboTimerHandle.IsValid();
}

void ACharacterBase::ComboActionBegin()
{
	CurrentCombo = 1;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (!AnimInstance) return;

	const float AttackSpeedRate = 1.f;
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);

	//if Play Montage, End Montage delegate subscribe
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ACharacterBase::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void ACharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProerlyEnded)
{
	ensure(CurrentCombo != 0);

	CurrentCombo = 0;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ACharacterBase::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;

	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = 1.f;
	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] /
		ComboActionData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime <= 0.f) return;

	GetWorld()->GetTimerManager().SetTimer
	(
		ComboTimerHandle,
		this,
		&ACharacterBase::ComboCheck,
		ComboEffectiveTime,
		false
	);
}

void ACharacterBase::ComboCheck()
{
	//Timer Initialize
	ComboTimerHandle.Invalidate();

	if (!HasNextComboCommand) return;

	//Montage Jump
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;
	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
	FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);

	AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);

	SetComboCheckTimer();

	HasNextComboCommand = false;
}

