// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Undegard_HUDHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class UNDEGARD_API UUndegard_HUDHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	float HealthPercent;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FLinearColor HealthColor;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FLinearColor FullHealthColor;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FLinearColor EmptyHealthColor;

public:
	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION()
	void Updatehealth(float CurrentHealth, float MaxHealth);
};
