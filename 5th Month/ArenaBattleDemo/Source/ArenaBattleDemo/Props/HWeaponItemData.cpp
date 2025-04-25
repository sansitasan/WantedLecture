// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/HWeaponItemData.h"

FPrimaryAssetId UHWeaponItemData::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("HItemData", GetFName());
}