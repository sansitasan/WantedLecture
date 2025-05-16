// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/ABFountain.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Net/UnrealNetwork.h"
#include "ArenaBattle.h"

// Sets default values
AABFountain::AABFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));

	RootComponent = Body;
	Water->SetupAttachment(Body);
	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 132.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01'"));
	if (BodyMeshRef.Object)
	{
		Body->SetStaticMesh(BodyMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WaterMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Fountain_02.SM_Plains_Fountain_02'"));
	if (WaterMeshRef.Object)
	{
		Water->SetStaticMesh(WaterMeshRef.Object);
	}

	bReplicates = true;

	SetNetUpdateFrequency(1.f);

	SetNetCullDistanceSquared(4000000.f);

	//SetNetDormancy(DORM_Initial);
}

// Called when the game starts or when spawned
void AABFountain::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]()
			{
				//ServerLightColor = FLinearColor(FMath::RandRange(0.f, 1.f), FMath::RandRange(0.f, 1.f), FMath::RandRange(0.f, 1.f), 1.f);
				//OnRep_ServerLightColor();
				//BigData.Init(BigDataElement, 1000);
				//BigDataElement += 1.f;
				//FLinearColor NewLightColor = FLinearColor(
				//	FMath::RandRange(0.f, 1.f), 
				//	FMath::RandRange(0.f, 1.f), 
				//	FMath::RandRange(0.f, 1.f), 
				//	1.f
				//);
				//MulticastRPCChangeLightColor(NewLightColor);
			}
		), 1.f, true);

		FTimerHandle Handle2;
		GetWorld()->GetTimerManager().SetTimer(Handle2, FTimerDelegate::CreateLambda([&]()
			{
				//FlushNetDormancy();
				for (auto Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					APlayerController* PlayerController = Iterator->Get();
					if (!PlayerController || !PlayerController->IsLocalPlayerController()) continue;
				}
			}
		), 10.f, false);
	}

	else 
	{
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]()
			{
				FLinearColor NewLightColor = FLinearColor(
					FMath::RandRange(0.f, 1.f),
					FMath::RandRange(0.f, 1.f),
					FMath::RandRange(0.f, 1.f),
					1.f
				);
				MulticastRPCChangeLightColor(NewLightColor);
				ServerRPCChangeLightColor();
			}
		), 1.f, true);
	}
}

void AABFountain::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AABFountain, ServerRotationYaw);
	DOREPLIFETIME(AABFountain, ServerRotationYaw2);
	DOREPLIFETIME(AABFountain, ServerLightColor);
	//DOREPLIFETIME_CONDITION(AABFountain, ServerLightColor, COND_InitialOnly);
	//DOREPLIFETIME(AABFountain, BigData);
}

void AABFountain::OnActorChannelOpen(FInBunch& InBunch, UNetConnection* Connection)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

bool AABFountain::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	bool NetRelevantResult = Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
	if (!NetRelevantResult) {
		AB_LOG(LogABNetwork, Log, 
			TEXT("Not Relevant: [%s] %s"), *RealViewer->GetName(), *SrcLocation.ToCompactString());
	}
	return NetRelevantResult;
}

void AABFountain::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PreReplication(ChangedPropertyTracker);
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AABFountain::ServerRPCChangeLightColor_Implementation()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AABFountain::MulticastRPCChangeLightColor_Implementation(FLinearColor NewLightColor)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	auto* PointLight = Cast<UPointLightComponent>(GetComponentByClass(UPointLightComponent::StaticClass()));
	if (PointLight) {
		PointLight->SetLightColor(NewLightColor);
	}
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

// Called every frame
void AABFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) {
		AddActorLocalRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));
		ServerRotationYaw = RootComponent->GetComponentRotation().Yaw;
		ServerRotationYaw2 = RootComponent->GetComponentRotation().Yaw;
		
	} else {
		//FRotator NewRotator = RootComponent->GetComponentRotation();
		//NewRotator.Yaw = ServerRotationYaw;
		//RootComponent->SetWorldRotation(NewRotator);
		ClientTimeSinceUpdate += DeltaTime;

		if (ClientTimeBetweenLastUpdate < KINDA_SMALL_NUMBER) {
			return;
		}

		//다음 네트워크 패킷 값 예측
		const float EstimateRotationYaw = ServerRotationYaw + RotationRate * ClientTimeBetweenLastUpdate;
		FRotator ClientRotator = RootComponent->GetComponentRotation();

		const float ClientNewYaw = FMath::Lerp(ServerRotationYaw, EstimateRotationYaw, ClientTimeSinceUpdate / ClientTimeBetweenLastUpdate);
		ClientRotator.Yaw = ClientNewYaw;
		RootComponent->SetWorldRotation(ClientRotator);
	}
}

void AABFountain::OnRep_ServerRotationYaw2()
{
	AB_LOG(LogABNetwork, Log, TEXT("%f"), ServerRotationYaw2);

	ClientTimeBetweenLastUpdate = ClientTimeSinceUpdate;
	ClientTimeSinceUpdate = 0.f;
}

void AABFountain::OnRep_ServerLightColor()
{
	if (!HasAuthority()) {
		AB_LOG(LogABNetwork, Log, TEXT("LightColor: %s"), *ServerLightColor.ToString());
	}
}
