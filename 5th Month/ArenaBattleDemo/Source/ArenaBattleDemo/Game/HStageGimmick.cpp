// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HStageGimmick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Physics/HCollision.h"
#include "Character/CharacterNonPlayer.h"
#include "Props/HItemBox.h"

// Sets default values
AHStageGimmick::AHStageGimmick()
{
	Stage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stage"));
	RootComponent = Stage;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StageMeshRef(TEXT("/Game/ArenaBattle/Environment/Stages/SM_SQUARE.SM_SQUARE"));
	if (StageMeshRef.Object) {
		Stage->SetStaticMesh(StageMeshRef.Object);
	}
	StageTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("StageTrigger"));
	StageTrigger->SetBoxExtent(FVector(775.f, 775.f, 300.f));
	StageTrigger->SetupAttachment(Stage);
	StageTrigger->SetRelativeLocation(FVector(0.f, 0.f, 250.f));
	StageTrigger->SetCollisionProfileName(CPROFILE_HTRIGGER);
	StageTrigger->OnComponentBeginOverlap.AddDynamic(
		this,
		&AHStageGimmick::OnStageTriggerBeginOverlap
	);

	static FName GateSockets[] = { TEXT("+XGATE"), TEXT("-XGATE"), TEXT("+YGATE"), TEXT("-YGATE") };

	static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMeshRef(TEXT("/Game/ArenaBattle/Environment/Props/SM_GATE.SM_GATE"));
	for (const FName& GateSocket : GateSockets) {
		UStaticMeshComponent* Gate = CreateDefaultSubobject<UStaticMeshComponent>(GateSocket);
		if (GateMeshRef.Object) {
			Gate->SetStaticMesh(GateMeshRef.Object);
		}

		Gates.Add(GateSocket, Gate);
		Gate->SetupAttachment(Stage, GateSocket);
		Gate->SetRelativeLocation(FVector(0.f, -80.f, 0.f));
		Gate->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

		FName TriggerName = *GateSocket.ToString().Append("Trigger");
		UBoxComponent* GateTrigger = CreateDefaultSubobject<UBoxComponent>(TriggerName);
		GateTrigger->SetBoxExtent(FVector(100.f, 100.f, 300.f));
		GateTrigger->SetupAttachment(Stage, GateSocket);
		GateTrigger->SetRelativeLocation(FVector(70.f, 0.f, 250.f));
		GateTrigger->SetCollisionProfileName(CPROFILE_HTRIGGER);
		GateTrigger->OnComponentBeginOverlap.AddDynamic(
			this,
			&AHStageGimmick::OnGateTriggerBeginOverlap
		);
		GateTrigger->ComponentTags.Add(GateSocket);

		GateTriggers.Add(GateTrigger);
	}

	SetState(EStageState::Ready);

	StageChangedActions.Add(
		EStageState::Ready, 
		FOnStageChangedDelegateWrapper(
			FOnStageChangedDelegate::CreateUObject(
				this, 
				&AHStageGimmick::SetReady)
		)
	);

	StageChangedActions.Add(
		EStageState::Fight,
		FOnStageChangedDelegateWrapper(
			FOnStageChangedDelegate::CreateUObject(
				this,
				&AHStageGimmick::SetFight)
		)
	);

	StageChangedActions.Add(
		EStageState::Reward,
		FOnStageChangedDelegateWrapper(
			FOnStageChangedDelegate::CreateUObject(
				this,
				&AHStageGimmick::SetChooseReward)
		)
	);

	StageChangedActions.Add(
		EStageState::Next,
		FOnStageChangedDelegateWrapper(
			FOnStageChangedDelegate::CreateUObject(
				this,
				&AHStageGimmick::SetChooseNext)
		)
	);

	OpponentSpawnTime = 2.f;
	OpponentClass = ACharacterNonPlayer::StaticClass();
	RewardItemClass = AHItemBox::StaticClass();
	//OpponentClass = AHItemBox::StaticClass();

	for (const FName& GateSocket : GateSockets) {
		FVector BoxLocation = Stage->GetSocketLocation(GateSocket) * 0.5f;

		RewardBoxLocations.Add(GateSocket, BoxLocation);
	}
}

void AHStageGimmick::OnConstruction(const FTransform& Transform)
{
	SetState(CurrentState);
}

void AHStageGimmick::SetState(EStageState InNewState)
{
	//if (CurrentState == InNewState) return;
	UE_LOG(LogTemp, Log, TEXT("SetState, %i"), InNewState);
	CurrentState = InNewState;
	if (StageChangedActions.Contains(InNewState)) {
		StageChangedActions[CurrentState].StageChangedDelegate.ExecuteIfBound();
	}
}

void AHStageGimmick::OnStageTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetState(EStageState::Fight);
}

void AHStageGimmick::SetReady()
{
	StageTrigger->SetCollisionProfileName(CPROFILE_HTRIGGER);
	for (const auto& GateTrigger : GateTriggers) {
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

void AHStageGimmick::SetFight()
{
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (const auto& GateTrigger : GateTriggers) {
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}

	CloseAllGates();

	GetWorld()->GetTimerManager().SetTimer(
		OpponentTimerHandle,
		this,
		&AHStageGimmick::OpponentSpawn,
		OpponentSpawnTime,
		false
	);
}

void AHStageGimmick::SetChooseReward()
{
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (const auto& GateTrigger : GateTriggers) {
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}

	CloseAllGates();

	SpawnRewardBoxes();
}

void AHStageGimmick::SetChooseNext()
{
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (const auto& GateTrigger : GateTriggers) {
		GateTrigger->SetCollisionProfileName(CPROFILE_HTRIGGER);
	}

	OpenAllGates();
}

void AHStageGimmick::OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ensure(OverlappedComponent->ComponentTags.Num() == 1);

	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(2));

	check(Stage->DoesSocketExist(SocketName));

	FTransform SpawnTransform(Stage->GetSocketLocation(SocketName));

	TArray<FOverlapResult> OverlapResults;

	FCollisionQueryParams CollisionQueryParams(
		SCENE_QUERY_STAT(GateTrigger),
		false,
		this
	);

	bool Result = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		SpawnTransform.GetLocation(),
		FQuat::Identity,
		FCollisionObjectQueryParams::InitType::AllStaticObjects,
		FCollisionShape::MakeSphere(775.f),
		CollisionQueryParams
	);

	if (Result) return;
	AHStageGimmick* NewGimmick = GetWorld()->SpawnActorDeferred<AHStageGimmick>(AHStageGimmick::StaticClass(), SpawnTransform);
	if (!NewGimmick) return;
	NewGimmick->SetStageNum(CurrentStageNum + 1);
	NewGimmick->FinishSpawning(SpawnTransform);
}

void AHStageGimmick::OpenAllGates()
{
	for (const auto& Gate : Gates) {
		Gate.Value->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}
}

void AHStageGimmick::CloseAllGates()
{
	for (const auto& Gate : Gates) {
		Gate.Value->SetRelativeRotation(FRotator::ZeroRotator);
	}
}

void AHStageGimmick::OpponentDestroyed(AActor* DestroyedActor)
{
	SetState(EStageState::Reward);
}

void AHStageGimmick::OpponentSpawn()
{
	const FTransform SpawnTransform = FTransform(GetActorLocation() + FVector::UpVector * 88.f);
	
	ACharacterNonPlayer* HOpponentCharacter = GetWorld()->SpawnActorDeferred<ACharacterNonPlayer>(OpponentClass, SpawnTransform);
	if (!HOpponentCharacter) return;
	HOpponentCharacter->SetLevel(CurrentStageNum);
	HOpponentCharacter->OnDestroyed.AddDynamic(this, &AHStageGimmick::OpponentDestroyed);
	HOpponentCharacter->FinishSpawning(SpawnTransform);
}

void AHStageGimmick::OnReawrdTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (const auto& RewardBox : RewardBoxes) 
	{
		if (!RewardBox.IsValid()) continue;
		AHItemBox* ValidBox = RewardBox.Get();
		AActor* OverlappedBox = OverlappedComponent->GetOwner();

		if (OverlappedBox != ValidBox)
		{
			ValidBox->Destroy();
		}
	}

	SetState(EStageState::Next);
}

void AHStageGimmick::SpawnRewardBoxes()
{
	for (const auto& RewardBoxLocation : RewardBoxLocations) 
	{
		FTransform SpawnTransform(GetActorLocation() + RewardBoxLocation.Value + FVector(0.f, 0.f, 30.f));
		AHItemBox* RewardBoxActor = GetWorld()->SpawnActorDeferred<AHItemBox>(RewardItemClass, SpawnTransform);
		if (!RewardBoxActor) return;
		RewardBoxActor->Tags.Add(RewardBoxLocation.Key);
		RewardBoxActor->GetTrigger()->OnComponentBeginOverlap.AddDynamic(
			this, &AHStageGimmick::OnReawrdTriggerBeginOverlap
		);

		RewardBoxes.Add(RewardBoxActor);
	}

	for (const auto& RewardBox : RewardBoxes) {
		if (!RewardBox.IsValid()) continue;
		RewardBox.Get()->FinishSpawning(RewardBox.Get()->GetActorTransform());
	}
}

