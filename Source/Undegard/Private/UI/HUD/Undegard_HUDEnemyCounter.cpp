// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/Undegard_HUDEnemyCounter.h"
#include "Core/Undegard_GameInstance.h"

void UUndegard_HUDEnemyCounter::InitializedWidget()
{
	GameInstanceReference = Cast<UUndegard_GameInstance>(GetWorld()->GetGameInstance());
	
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->OnEnemyKilledDelegate.AddDynamic(this,&UUndegard_HUDEnemyCounter::UpdateCounter);
		UpdateCounter(GameInstanceReference->GetDefeatedEnemiesCounter());
	}
}

void UUndegard_HUDEnemyCounter::UpdateCounter(int EnemiesDefeatedCounter)
{
	EnemiesDefeated = EnemiesDefeatedCounter;
}
