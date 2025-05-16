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

	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCChangeLightColor(FLinearColor NewLightColor);

	UFUNCTION(Server, Unreliable)
	void ServerRPCChangeLightColor();

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

	UFUNCTION()
	void OnRep_ServerLightColor();

	UPROPERTY(ReplicatedUsing = OnRep_ServerRotationYaw2)
	float ServerRotationYaw2;

	//UPROPERTY(Replicated)
	//TArray<float> BigData;
	//
	//float BigDataElement = 0.f;

	UPROPERTY(ReplicatedUsing = OnRep_ServerLightColor)
	FLinearColor ServerLightColor;

	float RotationRate = 30.f;

	float ClientTimeSinceUpdate = 0.f;

	float ClientTimeBetweenLastUpdate = 0.f;
};
