// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Undegard_GameMode.generated.h"

class AUndegard_Character;
class AUndegard_SpectatingCamera;
/**
 * 
 */
UCLASS()
class UNDEGARD_API AUndegard_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	AUndegard_SpectatingCamera* VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	AUndegard_SpectatingCamera* GameOverCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spectating Camera")
	float SpectatingBlendTime;

public:
	UFUNCTION()
	void Victory(AUndegard_Character* Character);

	UFUNCTION()
	void GameOver(AUndegard_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory(AUndegard_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver(AUndegard_Character* Character);

protected:
	virtual void BeginPlay() override;

	void SetUpSpectatingCameras();

	void MoveCameraToSpectatingPoint(AUndegard_SpectatingCamera* SpectatingCamera, AUndegard_Character* Character);
};
