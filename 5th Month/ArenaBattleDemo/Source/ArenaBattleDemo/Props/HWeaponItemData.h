// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/HItemData.h"
#include "HWeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEDEMO_API UHWeaponItemData : public UHItemData
{
	GENERATED_BODY()
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSoftObjectPtr<class USkeletalMesh> WeaponMesh;
};
