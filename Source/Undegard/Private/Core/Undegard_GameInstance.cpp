// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Undegard_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSystem/Undegard_SaveGame.h"

UUndegard_GameInstance::UUndegard_GameInstance() {
	SaveSlotName = "Undegard_SaveData";
}

void UUndegard_GameInstance::AddDefeatedEnemyCounter()
{
	DefetedEnemiesCounter++;
	OnEnemyKilledDelegate.Broadcast(DefetedEnemiesCounter);
	BP_AddDefeatedEnemyCounter();
}

void UUndegard_GameInstance::SaveData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);
	if (bExistingData)
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	}
	else
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(UUndegard_SaveGame::StaticClass());
	}
	if (IsValid(SaveGameObject))
	{
		UUndegard_SaveGame* SaveFile = Cast<UUndegard_SaveGame>(SaveGameObject);
		if (IsValid(SaveFile))
		{
			SaveFile->SetDefeatedEnemiesCounterInfo(DefetedEnemiesCounter);

			UGameplayStatics::SaveGameToSlot(SaveFile,SaveSlotName, 0);
		}
	}
}

void UUndegard_GameInstance::LoadData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);
	if (bExistingData)
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	}
	if (IsValid(SaveGameObject))
	{
		UUndegard_SaveGame* SaveFile = Cast<UUndegard_SaveGame>(SaveGameObject);
		if (IsValid(SaveFile))
		{
			DefetedEnemiesCounter = SaveFile->GetDefeatedEnemiesCounterInfo();
		}
	}
}

void UUndegard_GameInstance::ResetData()
{
	DefetedEnemiesCounter = 0;
	BP_ResetData();
}
