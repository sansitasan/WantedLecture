// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LCharacter.h"
#include "Character/LPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Tag/LGameplayTag.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ALCharacter::ALCharacter()
{
	ASC = nullptr;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(RootComponent);

	Camera->SetupAttachment(SpringArm);
}

void ALCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!NewController) return;

	ALPlayerState* LPS = GetPlayerState<ALPlayerState>();
	if (!LPS) return;
	int32 InputId = 0;
	ASC = LPS->GetAbilitySystemComponent();
	ASC->InitAbilityActorInfo(LPS, this);
	for (const auto& StartAbility : StartAbilities) {
		FGameplayAbilitySpec Spec(StartAbility);
		Spec.InputID = InputId++;

		ASC->GiveAbility(Spec);
	}

	for (const auto& StartInputAbility : StartInputAbilities) {
		FGameplayAbilitySpec Spec(StartInputAbility.Value);
		Spec.InputID = StartInputAbility.Key;

		ASC->GiveAbility(Spec);
	}

	SetupGASInputComponent();

	APlayerController* PlayerController = CastChecked<APlayerController>(NewController);
	PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));

	auto SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	SubSystem->AddMappingContext(DefaultMappingContext, 0);
}

// Called when the game starts or when spawned
void ALCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ALCharacter::SetupGASInputComponent()
{
	if (!IsValid(ASC) || !IsValid(InputComponent)) return;
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALCharacter::Move);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ALCharacter::GASInputPressed, 1);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ALCharacter::GASInputPressed, 2);
}

void ALCharacter::GASInputPressed(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (!Spec) return;
	if (Spec->IsActive()) {
		ASC->AbilitySpecInputPressed(*Spec);
	}
	else {
		Spec->InputPressed = true;
		ASC->TryActivateAbility(Spec->Handle);
	}
}

void ALCharacter::GASInputReleased(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (!Spec) return;
	ASC->AbilitySpecInputReleased(*Spec);
}

void ALCharacter::Move(const FInputActionValue& Value)
{
	FVector Movement(Value.Get<FVector2D>(), 0.f);

	FRotator Rotator;
	Rotator.Yaw = SpringArm ? -SpringArm->GetRelativeRotation().Yaw : 0.f;
	Movement = Rotator.RotateVector(Movement);

	AddMovementInput(Movement);
	SetActorRotation(Movement.ToOrientationRotator());
} 

void ALCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SetupGASInputComponent();
}

UAbilitySystemComponent* ALCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

