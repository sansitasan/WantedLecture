// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/ComboActionData.h"
#include "Physics/HCollision.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_HCAPSULE);
	//�ַ� �������� �޽��ݸ����� �����
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));


	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Game/ArenaBattle/Animation/AM_ComboAttack.AM_ComboAttack"));
	if (ComboActionMontageRef.Object) {
		ComboActionMontage = ComboActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Game/ArenaBattle/Animation/AM_Dead.AM_Dead"));
	if (DeadMontageRef.Object) {
		DeadMontage = DeadMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UComboActionData> ComboActionDataRef(TEXT("/Game/ArenaBattle/ComboAction/ABA_ComboAction.ABA_ComboAction"));

	if (ComboActionDataRef.Object) {
		ComboActionData = ComboActionDataRef.Object;
	}
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

void ACharacterBase::AttackHitCheck()
{
	FHitResult OutHitResult;

	FVector Start 
		= GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();

	const float AttackRange = 50.f;
	FVector End
		= Start + GetActorForwardVector() * AttackRange;

	FCollisionQueryParams Params(
	SCENE_QUERY_STAT(Attack),
		false,
		this);

	const float AttackRadius = 50.f;

	bool HitDetected = GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start,
		End,
		FQuat::Identity,
		CCHANNEL_HACTION,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * .5f;
	float CapsuleHalfHeight = AttackRange * .5f;

	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(
		GetWorld(),
		CapsuleOrigin,
		CapsuleHalfHeight,
		AttackRadius,
		FRotationMatrix::MakeFromX(GetActorForwardVector()).ToQuat(),
		DrawColor,
		false,
		5.f
	);
#endif

	if (!HitDetected) return;

	const float AttackDamage = 20.f;
	FDamageEvent DamageEvent;
	OutHitResult.GetActor()->TakeDamage(
		AttackDamage,
		DamageEvent,
		GetController(),
		this
	);
}

float ACharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//San Todo
	SetDead();
	return DamageAmount;
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

void ACharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	SetActorEnableCollision(false);

	PlayDeadAnimation();
}

void ACharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;
	AnimInstance->StopAllMontages(.0f);

	const float PlayRate = 1.f;
	AnimInstance->Montage_Play(DeadMontage, PlayRate);
}

