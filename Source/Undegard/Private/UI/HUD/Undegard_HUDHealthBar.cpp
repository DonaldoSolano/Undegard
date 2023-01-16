// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/Undegard_HUDHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "Undegard_Character.h"
#include "Character/Components/Undegard_HealthComponent.h"

void UUndegard_HUDHealthBar::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		AUndegard_Character* PlayerCharacter = Cast<AUndegard_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter))
		{
			UUndegard_HealthComponent* PlayerHealthComponent = PlayerCharacter->GetHealthComponent();
			if (IsValid(PlayerHealthComponent))
			{
				PlayerHealthComponent->OnHealthUpdateDelegate.AddDynamic(this, &UUndegard_HUDHealthBar::Updatehealth);
			}
		}
	}
}

void UUndegard_HUDHealthBar::Updatehealth(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
	HealthColor = FMath::Lerp(EmptyHealthColor, FullHealthColor, HealthPercent);
}
