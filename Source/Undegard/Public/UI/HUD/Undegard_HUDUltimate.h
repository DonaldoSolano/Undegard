// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Undegard_HUDUltimate.generated.h"

/**
 * 
 */
UCLASS()
class UNDEGARD_API UUndegard_HUDUltimate : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	float UltimatePercent;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FLinearColor UltimateColor;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FLinearColor UltimateEnabledColor;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FLinearColor UltimateDisabledColor;


public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION(BlueprintCallable)
	void UpdateUltimateValue(float CurrentUltimateXP, float MaxUltimateXP);

	UFUNCTION(BlueprintCallable)
	void UpdateUltimateStatus(bool bIsAvailable);
};
