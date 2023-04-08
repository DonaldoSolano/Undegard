// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Undegard_GameMode.generated.h"

class AUndegard_Character;
class AUndegard_SpectatingCamera;
class USoundCue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKeyAddedSignature, FName, KeyTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStateChange);

UCLASS()
class UNDEGARD_API AUndegard_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
		AUndegard_GameMode();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	AUndegard_SpectatingCamera* VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	AUndegard_SpectatingCamera* GameOverCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spectating Camera")
	float SpectatingBlendTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
	FName MainMenuMapName;

	FTimerHandle TimerHandle_BackToMainMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music")
	USoundCue* VictoryMusic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music")
	USoundCue* GameOverMusic;

public:

	UPROPERTY(BlueprintAssignable)
	FOnKeyAddedSignature OnKeyAddedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnGameStateChange OnVictoryDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnGameStateChange OnGameOverDelegate;

public:

	UFUNCTION()
	void AddKeyToCharacter(AUndegard_Character* KeyOwner, FName KeyTag);

	UFUNCTION()
	void Victory(AUndegard_Character* Character);

	UFUNCTION()
	void GameOver(AUndegard_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory(AUndegard_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver(AUndegard_Character* Character);

	void BackToMainMenu();

protected:
	virtual void BeginPlay() override;

	void SetUpSpectatingCameras();

	void MoveCameraToSpectatingPoint(AUndegard_SpectatingCamera* SpectatingCamera, AUndegard_Character* Character);

	void PlayGameModeMusic( USoundCue* MusicCue);
};
