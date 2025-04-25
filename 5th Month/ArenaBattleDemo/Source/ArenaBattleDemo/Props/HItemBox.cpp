// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/HItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Interface/HCharacterItemInterface.h"
#include "Physics/HCollision.h"
#include "Engine/AssetManager.h"
#include "HWeaponItemData.h"

// Sets default values
AHItemBox::AHItemBox()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_HTRIGGER);
	Trigger->SetBoxExtent(FVector(40.f, 42.f, 30.f));
	//Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHItemBox::OnOverlapBegin);

	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Game/ArenaBattle/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if (BoxMeshRef.Object) {
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}

	Mesh->AddRelativeLocation(FVector(0.f, -3.5f, -30.f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Game/ArenaBattle/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if (EffectRef.Object) {
		Effect->SetTemplate(EffectRef.Object);
		Effect->bAutoActivate = false;
	}
}

void AHItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Item) {
		Destroy();
		return;
	}

	IHCharacterItemInterface* overlappedPawn = Cast<IHCharacterItemInterface>(OtherActor);

	if (!overlappedPawn) return;
	overlappedPawn->TakeItem(Item);

	Effect->Activate();
	Mesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);

	Effect->OnSystemFinished.AddDynamic(this, &AHItemBox::OnEffectFinished);
}

void AHItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

void AHItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UAssetManager& Manager = UAssetManager::Get();
	TArray<FPrimaryAssetId> Assets;
	Manager.GetPrimaryAssetIdList(TEXT("HItemData"), Assets);

	ensure(Assets.Num() > 0);

	int32 RandomIndex = FMath::RandRange(0, Assets.Num() - 1);

	FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets[RandomIndex]));

	if (AssetPtr.IsPending()) 
	{
		AssetPtr.LoadSynchronous();
	}

	Item = Cast<UHItemData>(AssetPtr.Get());
	ensure(Item);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHItemBox::OnOverlapBegin);
}
