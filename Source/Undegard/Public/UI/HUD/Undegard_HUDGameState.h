// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Undegard_HUDGameState.generated.h"

/**
 * 
 */

class AUndegard_GameMode;

UCLASS()
class UNDEGARD_API UUndegard_HUDGameState : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FName GameStateName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FName VictoryName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FName GameOverName;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	AUndegard_GameMode* GameModeReference;

public:
	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION()
	void OnVictory();

	UFUNCTION()
	void OnGameOver();
};
