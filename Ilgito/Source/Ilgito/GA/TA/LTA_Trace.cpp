// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/TA/LTA_Trace.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystemComponent.h"
#include "Attribute/LCharacterAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

ALTA_Trace::ALTA_Trace()
{
}

void ALTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

bool ALTA_Trace::IsConfirmTargetingAllowed()
{
	return Super::IsConfirmTargetingAllowed();
}

void ALTA_Trace::ConfirmTargetingAndContinue()
{
	if (!SourceActor) return;

	FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
	TargetDataReadyDelegate.Broadcast(DataHandle);
	//Super::ConfirmTargetingAndContinue();
}

FGameplayAbilityTargetDataHandle ALTA_Trace::MakeTargetData() const
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);

	if (!ASC) return FGameplayAbilityTargetDataHandle();

	const ULCharacterAttributeSet* AttributeSet = ASC->GetSet<ULCharacterAttributeSet>();

	if (!AttributeSet) return FGameplayAbilityTargetDataHandle();



	FHitResult OutHitResult;
	const float AttackRange = AttributeSet->GetAttackRange();
	const float AttackRadius = AttributeSet->GetAttackRadius();

	FCollisionQueryParams(SCENE_QUERY_STAT(ULTA_Trace), false, Character);
	const FVector Forward = Character->GetActorForwardVector();
	const FVector Start = Character->GetActorLocation() + 
		Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();

	const FVector End = Start + Forward * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel
	(
		OutHitResult,
		Start, End, FQuat::Identity, 
		ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AttackRadius)
	);

	FGameplayAbilityTargetDataHandle DataHandle;

	if (HitDetected)
	{
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(OutHitResult);
		DataHandle.Add(TargetData);
	}

	if (bShowDebug)
	{
		FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
		float CapsuleHalfHeight = AttackRange * 0.5f;

		FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

		DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight,
			AttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(),
			DrawColor, false, 1.f);
	}

	return DataHandle;
}
