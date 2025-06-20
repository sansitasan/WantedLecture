// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "LCharacter.generated.h"

UCLASS()
class ILGITO_API ALCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

	void SetupGASInputComponent();

	void GASInputPressed(int32 InputId);
	void GASInputReleased(int32 InputId);

	void Move(const struct FInputActionValue& Value);

protected:
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DashAction;
};
