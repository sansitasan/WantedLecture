// Fill out your copyright notice in the Description page of Project Settings.


#include "LCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
//#include "GA/LGA_Base.h"
#include "Abilities/GameplayAbility.h"
#include "Tag/LGameplayTag.h"
#include "Attribute/LCharacterAttributeSet.h"

// Sets default values
ALCharacterBase::ALCharacterBase()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttributeSet = CreateDefaultSubobject<ULCharacterAttributeSet>(TEXT("AttributeSet"));
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
	//FGameplayAbilitySpec Spec(ULGA_Base::StaticClass());
	for (const auto& StartAbility : StartAbilities) {
		FGameplayAbilitySpec Spec(StartAbility);
		ASC->GiveAbility(Spec);
	}
}

UAbilitySystemComponent* ALCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
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
	FGameplayTagContainer TargetTag(LTAG_ACTOR_ROTATE);
	if (!ASC->HasMatchingGameplayTag(LTAG_ACTOR_ROTATING))
	{
		ASC->TryActivateAbilitiesByTag(TargetTag);
	}

	else 
	{
		ASC->CancelAbilities(&TargetTag);
	}

	//FGameplayAbilitySpec* Base = ASC->FindAbilitySpecFromClass(ULGA_Base::StaticClass());
	//if (Base->IsActive()) 
	//{
	//	ASC->TryActivateAbility(Base->Handle);
	//}
	//
	//else 
	//{
	//	ASC->CancelAbilityHandle(Base->Handle);
	//}
}