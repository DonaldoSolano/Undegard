// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/Undegard_HUDUltimate.h"
#include "Kismet/GameplayStatics.h"
#include "Undegard_Character.h"

void UUndegard_HUDUltimate::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		AUndegard_Character* PlayerCharacter = Cast<AUndegard_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->OnUltimateUpdateDelegate.AddDynamic(this, &UUndegard_HUDUltimate::UpdateUltimateValue);
			PlayerCharacter->OnUltimateStatusDelegate.AddDynamic(this, &UUndegard_HUDUltimate::UpdateUltimateStatus);
		}
	}
}

void UUndegard_HUDUltimate::UpdateUltimateValue(float CurrentUltimateXP, float MaxUltimateXP)
{
	UltimatePercent = CurrentUltimateXP / MaxUltimateXP;
}

void UUndegard_HUDUltimate::UpdateUltimateStatus(bool bIsAvailable)
{
	UltimateColor = bIsAvailable ? UltimateEnabledColor : UltimateDisabledColor;
}
