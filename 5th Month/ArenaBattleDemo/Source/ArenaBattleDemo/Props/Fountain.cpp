// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Fountain.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	///Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01'
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));
	///Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Fountain_02.SM_Plains_Fountain_02'

	RootComponent = Body;

	Water->SetupAttachment(Body);
	Water->SetRelativeLocation(FVector(0.f, 0.f, 140.f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> FountainBody(TEXT("/Game/ArenaBattle/Environment/Props/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> FountainWater(TEXT("/Game/ArenaBattle/Environment/Props/SM_Plains_Fountain_02.SM_Plains_Fountain_02"));
	if (FountainBody.Object) {
		Body->SetStaticMesh(FountainBody.Object);
	}

	if (FountainWater.Object) {
		Water->SetStaticMesh(FountainWater.Object);
	}
}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

