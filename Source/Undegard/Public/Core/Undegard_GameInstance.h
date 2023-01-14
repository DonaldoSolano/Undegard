// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Undegard_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNDEGARD_API UUndegard_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UUndegard_GameInstance();

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "SaveSystem")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "Enemy Data")
	int DefetedEnemiesCounter;

public:
	UFUNCTION(BlueprintCallable)
	int GetDefeatedEnemiesCounter() { return DefetedEnemiesCounter; };

	UFUNCTION(BlueprintCallable)
	void SetDefeatedEnemiesCounter(int NewValue) { DefetedEnemiesCounter = NewValue; };
	
	UFUNCTION(BlueprintCallable)
	void AddDefeatedEnemyCounter();

	UFUNCTION(BlueprintCallable)
	void SaveData();

	UFUNCTION(BlueprintCallable)
	void LoadData();

	UFUNCTION(BlueprintCallable)
	void ResetData();

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void BP_AddDefeatedEnemyCounter();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SaveData();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_LoadData();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ResetData();
};
