// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Undegard_GameMode.generated.h"

class AUndegard_Character;
/**
 * 
 */
UCLASS()
class UNDEGARD_API AUndegard_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Victory(AUndegard_Character* Character);

	UFUNCTION()
	void GameOver();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory(AUndegard_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver();
};
