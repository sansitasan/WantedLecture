// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CharacterPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <EnhancedInputLibrary.h>

ACharacterPlayer::ACharacterPlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));


	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera->SetupAttachment(SpringArm);

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Game/ArenaBattle/Input/IMC_Default.IMC_Default"));
	if (InputMappingContextRef.Object) {
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Game/ArenaBattle/Input/Actions/IA_Jump.IA_Jump"));
	if (JumpActionRef.Object) {
		JumpAction = JumpActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Game/ArenaBattle/Input/Actions/IA_Look.IA_Look"));
	if (LookActionRef.Object) {
		LookAction = LookActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Game/ArenaBattle/Input/Actions/IA_Move.IA_Move"));
	if (MoveActionRef.Object) {
		MoveAction = MoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionRef(TEXT("/Game/ArenaBattle/Input/Actions/IA_Attack.IA_Attack"));
	if (AttackActionRef.Object) {
		AttackAction = AttackActionRef.Object;
	}
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	//Checked = static assert Á¸Àç
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(PlayerController->GetLocalPlayer())) 
	{
		SubSystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::Look);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::Attack);
}

void ACharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();

	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardVector, Movement.Y);
	AddMovementInput(RightVector, Movement.X);
}

void ACharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D Look = Value.Get<FVector2D>();

	AddControllerYawInput(Look.X);
	AddControllerPitchInput(Look.Y);
}

void ACharacterPlayer::Attack()
{
	ProcessComboCommand();
}
