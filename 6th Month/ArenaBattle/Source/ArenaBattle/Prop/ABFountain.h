// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABFountain.generated.h"

UCLASS()
class ARENABATTLE_API AABFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 액터 채널이 열릴 때 호출되는 함수.
	virtual void OnActorChannelOpen(class FInBunch& InBunch, class UNetConnection* Connection) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Water;

	UPROPERTY(Replicated)
	float ServerRotationYaw;

	UFUNCTION()
	void OnRep_ServerRotationYaw2();

	UPROPERTY(ReplicatedUsing = OnRep_ServerRotationYaw2)
	float ServerRotationYaw2;

	float RotationRate = 30.f;
};
