// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "LAT_Trance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);
/**
 * 
 */

class ALTA_Trace;

UCLASS()
class ILGITO_API ULAT_Trance : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	ULAT_Trance();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "WaitForTrace",
		HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static ULAT_Trance* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<ALTA_Trace> InTargetActorClass);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	void SpawnAndInitializeTargetActor();
	void FinalizeTargetActor();

	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnComplete;

protected:
	void OnTargetDataReadCallBack(const FGameplayAbilityTargetDataHandle& DataHandle);

	UPROPERTY()
	TSubclassOf<ALTA_Trace> TargetActorClass;

	UPROPERTY()
	TObjectPtr<ALTA_Trace> SpawnedTargetActor;
};
