// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/HItemData.h"

FPrimaryAssetId UHItemData::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("HItemData", GetFName());
}
