// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/Undegard_HUDObjectivesContainer.h"
#include "Core/Undegard_GameMode.h"
#include "UI/HUD/Undegard_HUDObjective.h"



void UUndegard_HUDObjectivesContainer::InitializeWidget()
{
	GameModeReference = Cast<AUndegard_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameModeReference))
	{
		GameModeReference->OnKeyAddedDelegate.AddDynamic(this, &UUndegard_HUDObjectivesContainer::UpdateObjectives);
	}
}

void UUndegard_HUDObjectivesContainer::InitializeObjectives(TArray<UUndegard_HUDObjective*> NewObjectives)
{
	for (UUndegard_HUDObjective* NewObjective : NewObjectives)
	{
		Objectives.AddUnique(NewObjective);
	}
}

void UUndegard_HUDObjectivesContainer::UpdateObjectives(FName KeyTag)
{
	int ObjectiveIndex = -1;

	if (KeyTag == "KeyA")
	{
		ObjectiveIndex = 0;
	}
	
	if (KeyTag == "KeyB")
	{
		ObjectiveIndex = 1;
	}

	if (Objectives.IsValidIndex(ObjectiveIndex))
	{
		UUndegard_HUDObjective* CurrentObjective = Objectives[ObjectiveIndex];
		if (IsValid(CurrentObjective))
		{
			CurrentObjective->ObjectiveCompleted();
		}
	}
}
