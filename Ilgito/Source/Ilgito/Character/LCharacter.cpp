// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LCharacter.h"
#include "Character/LPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Tag/LGameplayTag.h"
#include "EnhancedInputComponent.h"

void Test(AActor* Actor) 
{

}

// Sets default values
ALCharacter::ALCharacter()
{
	ASC = nullptr;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TObjectPtr<AActor> s = this;
	Test(s);
}

void ALCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

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
}

// Called when the game starts or when spawned
void ALCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALCharacter::SetupGASInputComponent()
{
	if (!IsValid(ASC) || !IsValid(InputComponent)) return;
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	//EnhancedInputComponent->BindAction(UInputAction, ETriggerEvent::Triggered, this, &ALCharacter::GASInputPressed, 0);
	//EnhancedInputComponent->BindAction(UInputAction, ETriggerEvent::Completed, this, &ALCharacter::GASInputReleased, 0);
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
	if (!Spec->IsActive()) return;
	ASC->AbilitySpecInputReleased(*Spec);
}

// Called every frame
void ALCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SetupGASInputComponent();
}

UAbilitySystemComponent* ALCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

