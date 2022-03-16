// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Character/Undegard_ANEnableAction.h"
#include "Undegard_Character.h"

void UUndegard_ANEnableAction::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AUndegard_Character* Character = Cast<AUndegard_Character>(CharacterActor);
		if (IsValid(Character))
		{
			Character->SetActionsState(false);
		}
	}
}
