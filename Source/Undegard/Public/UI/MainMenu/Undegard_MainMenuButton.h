// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Undegard_MainMenuButton.generated.h"

UENUM(Blueprintable)
enum class EUndegard_ButtonStyleType : uint8
{
	ButtonStyleType_Mouse UMETA(DisplayName = "Selected by mouse"),
	ButtonStyleType_KeySelected UMETA(DisplayName = "Selected by keyboard"),
	ButtonStyleType_KeyNotSelected UMETA(DisplayName = "Not Selected by keyboard")
};

UCLASS()
class UNDEGARD_API UUndegard_MainMenuButton : public UButton
{
	GENERATED_BODY()

public:
	UUndegard_MainMenuButton();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Menu Button")
	float CheckFocusRate;

	FTimerHandle TimerHandle_CheckFocus;

protected:


	UFUNCTION(BlueprintCallable, Category = "Main Menu Button")
	void Start();

	void CheckFocus();

	void SetButtonStyle(EUndegard_ButtonStyleType NewStyleType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Button Style Type")
	void BP_SetButtonStyle(EUndegard_ButtonStyleType NewStyleType);
};
