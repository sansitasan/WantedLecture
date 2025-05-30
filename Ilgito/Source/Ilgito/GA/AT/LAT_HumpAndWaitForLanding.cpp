// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/LAT_HumpAndWaitForLanding.h"
#include "GameFramework/Character.h"

ULAT_HumpAndWaitForLanding::ULAT_HumpAndWaitForLanding()
{
}

ULAT_HumpAndWaitForLanding* ULAT_HumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningAbility)
{
	ULAT_HumpAndWaitForLanding* NewTask = NewAbilityTask<ULAT_HumpAndWaitForLanding>(OwningAbility);
	return NewTask;
}

void ULAT_HumpAndWaitForLanding::Activate()
{
	Super::Activate();

	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->Jump();
	Character->LandedDelegate.AddDynamic(this, &ULAT_HumpAndWaitForLanding::OnLandedCallback);
	SetWaitingOnAvatar();

}

void ULAT_HumpAndWaitForLanding::OnDestroy(bool AbilityEnded)
{
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.RemoveDynamic(this, &ULAT_HumpAndWaitForLanding::OnLandedCallback);
	Super::OnDestroy(AbilityEnded);
}

void ULAT_HumpAndWaitForLanding::OnLandedCallback(const FHitResult& Hit)
{
	if (ShouldBroadcastAbilityTaskDelegates()) {
		OnComplete.Broadcast();
	}
}
