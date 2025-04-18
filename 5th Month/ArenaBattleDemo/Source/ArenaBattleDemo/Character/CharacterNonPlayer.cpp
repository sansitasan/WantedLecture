// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterNonPlayer.h"
#include "CharacterNonPlayer.h"

ACharacterNonPlayer::ACharacterNonPlayer()
{
}

void ACharacterNonPlayer::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		DeadTimerHandle, 
		FTimerDelegate::CreateLambda([&]() 
			{
				Destroy();
			}
		), 
		3.f, 
		false);
}
