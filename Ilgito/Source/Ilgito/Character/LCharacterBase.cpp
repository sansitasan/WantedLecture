// Fill out your copyright notice in the Description page of Project Settings.


#include "LCharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
ALCharacterBase::ALCharacterBase()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ASC->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* ALCharacterBase::GetAbilitySystemComponent() const
{
	return nullptr;
}

// Called every frame
void ALCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}