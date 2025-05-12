// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LMessageGameInstanceSubsystem.generated.h"
/**
 * 
 */
UCLASS()
class ILGITO_API ULMessageGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	template<typename T, typename std::enable_if<std::is_base_of<UObject, T>::value>::type*>
	void Publish(T message) 
	{
		UObject* notifier = nullptr;

	}

	template<typename T, typename std::enable_if<std::is_base_of<UObject, T>::value>::type*, typename RetValType, typename... ParamTypes>
	void Receive(T message, TMulticastDelegate<RetValType(ParamTypes...)> delegate)
	{
		UObject* notifier = nullptr;

	}

private:
	//TMap<UClass, TObjectPtr<UObject>> 
};
