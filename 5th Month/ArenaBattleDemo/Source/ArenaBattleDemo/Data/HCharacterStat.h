#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HCharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FHCharacterStat : public FTableRowBase {
	GENERATED_BODY()

public:
	FHCharacterStat()
		: MaxHp(0.f), Attack(0.f), AttackRange(0.f), AttackSpeed(0.f), MovementSpeed(0.f) { }

	FHCharacterStat operator+(const FHCharacterStat& other) const {

		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&other);
		FHCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FHCharacterStat) / sizeof(float);

		for (int32 i = 0; i < StatNum; ++i) {
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
		//MaxHp += other.MaxHp;
		//MaxHp += this->MaxHp;
		//
		//Attack += other.Attack;
		//Attack += this->Attack;
		//
		//AttackRange += other.AttackRange;
		//AttackRange += this->AttackRange;
		//
		//AttackSpeed += other.AttackSpeed;
		//AttackSpeed += this->AttackSpeed;
		//
		//MovementSpeed += other.MovementSpeed;
		//MovementSpeed += this->MovementSpeed;
	}

	virtual void Test() {
		MaxHp = 100.f;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;
};