// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * 
 */
class SDockTab;
class FSpawnTabArgs;
class ILGITO_API FLEditor : public IModuleInterface
{
public:
	FLEditor();
	~FLEditor();

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedRef<SDockTab> OnProjectSettingsTabSpawned(const FSpawnTabArgs& SpawnArgs);

	void OnProjectSettingsTabClosed(TSharedRef<SDockTab> ClosedTab);

	FDelegateHandle SpawnedHandle;

private:
	void OnModuleLoad(FName InModuleName, EModuleChangeReason Reason);
};
