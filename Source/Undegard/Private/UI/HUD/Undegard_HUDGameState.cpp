// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/Undegard_HUDGameState.h"
#include "Core/Undegard_GameMode.h"

void UUndegard_HUDGameState::InitializeWidget()
{
	GameModeReference = Cast<AUndegard_GameMode>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameModeReference))
	{
		GameModeReference->OnVictoryDelegate.AddDynamic(this, &UUndegard_HUDGameState::OnVictory); 
		GameModeReference->OnGameOverDelegate.AddDynamic(this, &UUndegard_HUDGameState::OnGameOver);
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UUndegard_HUDGameState::OnVictory()
{
	GameStateName = VictoryName;
	SetVisibility(ESlateVisibility::Visible);
}

void UUndegard_HUDGameState::OnGameOver()
{
	GameStateName = GameOverName;
	SetVisibility(ESlateVisibility::Visible);
}
