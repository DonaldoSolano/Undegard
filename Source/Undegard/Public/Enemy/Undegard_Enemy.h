// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Undegard_Character.h"
#include "Undegard_Enemy.generated.h"

/**
 * 
 */
class AUndegard_PathActor;
class AUndegard_Item;
class AUndegard_AIController;

UCLASS()
class UNDEGARD_API AUndegard_Enemy : public AUndegard_Character
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Navigation Path")
	AUndegard_PathActor* PathActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Navigation Path")
	bool bLoopPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Navigation Path")
	int DirectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Navigation Path")
	float WaitingTimeOnPathPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|XP")
	float XPValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot System")
	float LootProbability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot System")
	TSubclassOf<AUndegard_Item> LootItemClass;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Controller")
	AUndegard_AIController* MyAIController;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void GiveXP(AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_GiveXP(AActor* DamageCauser);

	UFUNCTION()
	void HealthChanged(UUndegard_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	bool TrySpawnLoot();

public:
	UFUNCTION()
	bool GetLoopPath() { return bLoopPath; };

	UFUNCTION()
	int GetDirectionIndex() { return DirectionIndex; };

	UFUNCTION()
	float GetWaitingTime() { return WaitingTimeOnPathPoint; };

public:
	AUndegard_Enemy();
};
