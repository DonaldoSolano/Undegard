// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Undegard_EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class UNDEGARD_API UUndegard_EnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	float HealthPercent;

public:

	UFUNCTION()
	void Updatehealth(float CurrentHealth, float MaxHealth);
};
