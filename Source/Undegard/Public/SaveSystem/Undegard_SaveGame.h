// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Undegard_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UNDEGARD_API UUndegard_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	int DefeatedEnemiesCounter;

public:
	UFUNCTION(BlueprintCallable)
		void SetDefeatedEnemiesCounterInfo(int NewValue) { DefeatedEnemiesCounter = NewValue; };

	UFUNCTION(BlueprintCallable)
		int GetDefeatedEnemiesCounterInfo() { return DefeatedEnemiesCounter; };
};
