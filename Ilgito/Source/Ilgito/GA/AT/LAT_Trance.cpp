// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/LAT_Trance.h"
#include "GA/TA/LTA_Trace.h"
#include "AbilitySystemComponent.h"

ULAT_Trance::ULAT_Trance()
{
}

ULAT_Trance* ULAT_Trance::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<ALTA_Trace> InTargetActorClass)
{
	ULAT_Trance* NewTask = NewAbilityTask<ULAT_Trance>(OwningAbility);
	NewTask->TargetActorClass = InTargetActorClass;
	return NewTask;
}

void ULAT_Trance::Activate()
{
	Super::Activate();

	SpawnAndInitializeTargetActor();
	FinalizeTargetActor();

	SetWaitingOnAvatar();
}

void ULAT_Trance::OnDestroy(bool AbilityEnded)
{
	if (SpawnedTargetActor) SpawnedTargetActor->Destroy();
	Super::OnDestroy(AbilityEnded);
}

void ULAT_Trance::SpawnAndInitializeTargetActor()
{
	SpawnedTargetActor = Cast<ALTA_Trace>(
		Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(
			TargetActorClass,
			FTransform::Identity,
			nullptr, nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		)
	);

	if (!SpawnedTargetActor) return;
	SpawnedTargetActor->SetShowDebug(true);
	SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &ULAT_Trance::OnTargetDataReadCallBack);
}

void ULAT_Trance::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (!ASC) return;

	const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
	SpawnedTargetActor->FinishSpawning(SpawnTransform);
	ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
	SpawnedTargetActor->StartTargeting(Ability);
	SpawnedTargetActor->ConfirmTargeting();
}

void ULAT_Trance::OnTargetDataReadCallBack(const FGameplayAbilityTargetDataHandle& DataHandle)
{

	if (ShouldBroadcastAbilityTaskDelegates()) {
		OnComplete.Broadcast(DataHandle);
	}

	EndTask();
}
