// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/Undegard_MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Core/Undegard_GameInstance.h"

void UUndegard_MainMenuWidget::NewGame()
{
	BP_NewGame();

	UUndegard_GameInstance* GameInstanceReference = Cast<UUndegard_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->ResetData();
	}

	UGameplayStatics::OpenLevel(GetWorld(), GamePlayLevelName); 
}

void UUndegard_MainMenuWidget::ContinueGame()
{
	BP_ContinueGame();

	UUndegard_GameInstance* GameInstanceReference = Cast<UUndegard_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->LoadData();
	}

	UGameplayStatics::OpenLevel(GetWorld(), GamePlayLevelName);

}

void UUndegard_MainMenuWidget::QuitGame()
{
	BP_QuitGame();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);

}
