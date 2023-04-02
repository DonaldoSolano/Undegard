// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/Undegard_HUDObjective.h"

void UUndegard_HUDObjective::ObjectiveCompleted()
{
	bIsCompleted = true;
	CurrentColor = CompletedColor;
}
