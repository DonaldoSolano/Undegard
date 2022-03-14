// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Launcher.h"
#include "Undegard_Projectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AUndegard_Launcher::AUndegard_Launcher()
{
	MuzzleSocketName = "SCK_Muzzle";
}

void AUndegard_Launcher::StartAction()
{
	Super::StartAction();

	AActor* CurrentOwner = GetOwner();

	if (IsValid(CurrentOwner))
	{
		FVector EyeLocation;

		FRotator EyeRotation;

		//For this method remember that the & sign in the description of the arguments indicates that the variables passed as arguments are empty and the method will
		//return info into them respectively. And the variable type before the method description indicate the type of variable of the information the method returns.
		CurrentOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(CurrentOwner);

		USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();

		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
			
			FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);
			
			AUndegard_Projectile* CurrentProjectile = GetWorld()->SpawnActor<AUndegard_Projectile>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotation);

			CurrentProjectile->ProjectileDamage = Damage;
			CurrentProjectile->ShotDirection = ShotDirection;
			CurrentProjectile->ControllerInstigator = CurrentOwner->GetInstigatorController();
			CurrentProjectile->ProjectileDamageType = DamageType;
		}
	}
}

void AUndegard_Launcher::StopAction()
{
	Super::StopAction();
}
