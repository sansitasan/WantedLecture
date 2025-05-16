// Fill out your copyright notice in the Description page of Project Settings.


#include "LEditor.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FYourModuleNameEditorModule"

static const FName ModuleName("ProjectSettings");

FLEditor::FLEditor()
{

}

FLEditor::~FLEditor()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ModuleName);
}

void FLEditor::StartupModule()
{
	FModuleManager::Get().OnModulesChanged().AddRaw(this, &FLEditor::OnModuleLoad);
}

void FLEditor::ShutdownModule()
{
}

TSharedRef<SDockTab> FLEditor::OnProjectSettingsTabSpawned(const FSpawnTabArgs& SpawnArgs)
{
	//ProjectSettingEntry->OnSpawnTab.Execute(SpawnArgs);
	TSharedPtr<SDockTab> Tab = FGlobalTabmanager::Get()->GetActiveTab();
	UE_LOG(LogTemp, Log, TEXT("Hello Module"));
	//Tab->SetOnTabClosed
	return Tab.ToSharedRef();
}

void FLEditor::OnProjectSettingsTabClosed(TSharedRef<SDockTab> ClosedTab)
{
}

void FLEditor::OnModuleLoad(FName InModuleName, EModuleChangeReason Reason)
{
	if (ModuleName != ModuleName || Reason != EModuleChangeReason::ModuleLoaded) return;
	ProjectSettingEntry = FGlobalTabmanager::Get()->FindTabSpawnerFor("ProjectSettings");
	//FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
	//	"ProjectSettings",
	//	FOnSpawnTab::CreateRaw(this, &FLEditor::OnProjectSettingsTabSpawned),
	//	FCanSpawnTab::CreateLambda([](FSpawnTabArgs const&) { return true; })
	//)
	//	.SetDisplayName(LOCTEXT("ProjectSettingsTabTitle", "Project Settings"))
	//	.SetMenuType(ETabSpawnerMenuType::Hidden);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLEditor, LEditor)