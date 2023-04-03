// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Undegard_HUDEnemyCounter.generated.h"

class UUndegard_GameInstance;
/**
 * 
 */
UCLASS()
class UNDEGARD_API UUndegard_HUDEnemyCounter : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	int EnemiesDefeated;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UUndegard_GameInstance* GameInstanceReference;

public:

	UFUNCTION(BlueprintCallable)
	void InitializedWidget();

	UFUNCTION()
	void UpdateCounter(int EnemiesDefeatedCounter);
};
