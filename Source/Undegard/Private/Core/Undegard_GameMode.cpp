// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Undegard_GameMode.h"
#include "Undegard_Character.h"

void AUndegard_GameMode::Victory(AUndegard_Character* Character)
{
	Character->DisableInput(nullptr);
	BP_Victory(Character);
}

void AUndegard_GameMode::GameOver()
{
	BP_GameOver();
}
