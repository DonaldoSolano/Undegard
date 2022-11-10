// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Undegard_AIController.generated.h"


class UBehaviorTree;
class AUndegard_Enemy;
class UBlackboardComponent;
class UAIPerceptionComponent;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAIPerceptionComponent* AIPerceptionComponent;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Enemy Controller")
	bool bReceivingDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	UBehaviorTree* EnemyBehaviorTree;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Controller")
	UBlackboardComponent* MyBlackBoard;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Controller")
	AUndegard_Enemy* MyEnemy;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Enemy Controller")
	FName LoopPathParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName DirectionIndexParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName WaitingTimeOnPointParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName CanSeePlayerParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName InvestigatingParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName TargetLocationParameterName;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateSenses(const TArray<AActor*>& UpdatedActors);

public:
	void SetReceiveDamage(bool bNewState) { bReceivingDamage = bNewState; };
};
