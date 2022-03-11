// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Launcher.h"
#include "Undegard_Projectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AUndegard_Launcher::AUndegard_Launcher()
{
	MuzzleSocketName = "SCK_Muzzle";
}

void AUndegard_Launcher::StartAction()
{
	Super::StartAction();

	if (IsValid(CurrentOwnerCharacter))
	{
		USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();

		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
			
			FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);
			
			AUndegard_Projectile* CurrentProjectile = GetWorld()->SpawnActor<AUndegard_Projectile>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotation);
		}
	}
}

void AUndegard_Launcher::StopAction()
{
	Super::StopAction();
}
