// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Udegard_DoorKey.h"
#include "..\..\Public\Items\Udegard_DoorKey.h"
#include "Undegard_Character.h"
#include "Core/Undegard_GameMode.h"

AUdegard_DoorKey::AUdegard_DoorKey()
{
	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMeshComponent->SetupAttachment(RootComponent);
	KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	KeyTag = "KeyA";
}

void AUdegard_DoorKey::Pickup(AUndegard_Character* PickupActor)
{
	Super::Pickup(PickupActor);

	if (IsValid(PickupActor) && PickupActor->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
	{
		if (IsValid(GameModeReference))
		{
			GameModeReference->AddKeyToCharacter(PickupActor, KeyTag);
			PickupActor->GainUltimateXP(XPValue);
		}
	}

	Destroy();
}
