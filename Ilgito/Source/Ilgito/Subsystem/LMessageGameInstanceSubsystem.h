// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LMessageGameInstanceSubsystem.generated.h"
/**
 * 
 */

template<typename MessageType>
using FMessageDelegate = TMulticastDelegate<void(const MessageType&)>;

struct IMessageDelegateContainer
{
	virtual ~IMessageDelegateContainer() = default;
};

template<typename MessageType>
struct TMessageDelegateContainer : IMessageDelegateContainer
{
	FMessageDelegate<MessageType> Delegate;
};

UCLASS()
class ILGITO_API ULMessageGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	template<typename MessageType>
	FDelegateHandle Subscribe(const typename FMessageDelegate<MessageType>::FDelegate& InDelegate)
	{
		const FName TypeName = MessageType::StaticStruct()->GetFName();
		auto* BasePtr = Containers.Find(TypeName);
		if (!BasePtr)
		{
			Containers.Add(TypeName, MakeUnique<TMessageDelegateContainer<MessageType>>());
			BasePtr = Containers.Find(TypeName);
		}

		auto* Container = static_cast<TMessageDelegateContainer<MessageType>*>(BasePtr->Get());
		return Container->Delegate.Add(InDelegate);
	}

	template<typename MessageType>
	void Unsubscribe(FDelegateHandle Handle)
	{
		const FName TypeName = MessageType::StaticStruct()->GetFName();
		if (auto* BasePtr = Containers.Find(TypeName))
		{
			auto* Container = static_cast<TMessageDelegateContainer<MessageType>*>(BasePtr->Get());
			Container->Delegate.Remove(Handle);
		}
	}

	template<typename MessageType>
	void Publish(const MessageType& Message)
	{
		const FName TypeName = MessageType::StaticStruct()->GetFName();
		if (auto* BasePtr = Containers.Find(TypeName))
		{
			auto* Container = static_cast<TMessageDelegateContainer<MessageType>*>(BasePtr->Get());
			Container->Delegate.Broadcast(Message);
		}
	}

private:
	TMap<FName, TUniquePtr<IMessageDelegateContainer>> Containers;
};
