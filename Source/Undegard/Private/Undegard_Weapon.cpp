// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Weapon.h"
#include "GameFramework/Character.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AUndegard_Weapon::AUndegard_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Damage = 20.0f;
}

// Called when the game starts or when spawned
void AUndegard_Weapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUndegard_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUndegard_Weapon::StartAction()
{
	PlaySound(ShotSound);
	BP_StartAction();
}

void AUndegard_Weapon::StopAction()
{
	BP_StopAction();
}

void AUndegard_Weapon::SetCharacterOwner(ACharacter * NewOwner)
{
	if (IsValid(NewOwner))
	{
		SetOwner(NewOwner);
		CurrentOwnerCharacter = NewOwner;
	}
}

void AUndegard_Weapon::PlaySound(USoundCue* SoundCue, bool bIs3D, FVector SoundLocation)
{
	if (!IsValid(SoundCue))
	{
		return;
	}

	if (bIs3D)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCue, SoundLocation);
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(),SoundCue);
	}
	
}

