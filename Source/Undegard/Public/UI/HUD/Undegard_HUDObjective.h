// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Undegard_HUDObjective.generated.h"

/**
 * 
 */
UCLASS()
class UNDEGARD_API UUndegard_HUDObjective : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	bool bIsCompleted;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Setup")
	FName ObjetiveName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor CurrentColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor CompletedColor;

public:
	void ObjectiveCompleted();
};
