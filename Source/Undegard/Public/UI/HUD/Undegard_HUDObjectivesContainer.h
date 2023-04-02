// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Undegard_HUDObjectivesContainer.generated.h"

class AUndegard_GameMode;
class UUndegard_HUDObjective;
/**
 * 
 */
UCLASS()
class UNDEGARD_API UUndegard_HUDObjectivesContainer : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	AUndegard_GameMode* GameModeReference;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	TArray<UUndegard_HUDObjective*> Objectives;



public:
	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION(BlueprintCallable)
	void InitializeObjectives(TArray<UUndegard_HUDObjective*> NewObjectives);

	UFUNCTION()
	void UpdateObjectives(FName KeyTag);
};
