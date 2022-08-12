// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Undegard_Enemy.h"
#include "Enemy/Undegard_PathActor.h"
#include "Character/Components/Undegard_HealthComponent.h"
#include "Undegard_Character.h"
#include "Undegard_Rifle.h"
#include "Items/Undegard_Item.h"

void AUndegard_Enemy::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeadDelegate.AddDynamic(this, &AUndegard_Enemy::GiveXP);
}

void AUndegard_Enemy::GiveXP(AActor * DamageCauser)
{
	AUndegard_Character* Player = Cast<AUndegard_Character>(DamageCauser);

	if (IsValid(Player) && Player->GetCharacterType()==EUndegard_CharacterType::CharacterType_Player)
	{
		Player->GainUltimateXP(XPValue);
	}

	AUndegard_Rifle* Rifle = Cast<AUndegard_Rifle>(DamageCauser);
	if (IsValid(Rifle))
	{
		AUndegard_Character* RifleOwner = Cast<AUndegard_Character>(Rifle->GetOwner());
		if (IsValid(RifleOwner) && RifleOwner->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
		{
			RifleOwner->GainUltimateXP(XPValue);
			TrySpawnLoot();
		}
	}

	BP_GiveXP(DamageCauser);
}

bool AUndegard_Enemy::TrySpawnLoot()
{
	if (!IsValid(LootItemClass))
	{
		return false;
	}

	float SelectedProbability = FMath::RandRange(0.0f, 100.0f);

	if (SelectedProbability<=LootProbability)
	{
		//Create the parameters structure object.
		FActorSpawnParameters SpawnParameters;

		//Spawn the object event if there is a collision on that point.
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//Spawn the object.
		GetWorld()->SpawnActor<AUndegard_Item>(LootItemClass,GetActorLocation(),FRotator::ZeroRotator, SpawnParameters);
	}

	return true;
}

AUndegard_Enemy::AUndegard_Enemy() {
	bLoopPath = false;
	DirectionIndex = 1;
	WaitingTimeOnPathPoint = 1.0f;
	XPValue = 15.0f;
	LootProbability = 100.0f;
}