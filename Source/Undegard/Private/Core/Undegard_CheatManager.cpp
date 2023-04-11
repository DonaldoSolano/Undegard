// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Undegard_CheatManager.h"
#include "Kismet/GameplayStatics.h"
#include "Undegard_Character.h"


void UUndegard_CheatManager::Undegard_UltimateReady()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		AUndegard_Character* PlayerCharacter = Cast<AUndegard_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter) && PlayerCharacter->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
		{
			PlayerCharacter->GainUltimateXP(10000);
		}
	}
}
