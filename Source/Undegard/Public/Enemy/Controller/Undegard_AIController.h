// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Undegard_AIController.generated.h"


class UBehaviorTree;
class AUndegard_Enemy;

/**
 * 
 */
UCLASS()
class UNDEGARD_API AUndegard_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AUndegard_AIController();



protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	UBehaviorTree* EnemyBehaviorTree;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Controller")
	AUndegard_Enemy* MyEnemy;

protected:
	virtual void BeginPlay() override;
};
