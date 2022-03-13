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
		/*FVector EyeLocation;

		FRotator EyeRotation;

		CurrentOwnerCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * TraceLenght);*/

		USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();

		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
			
			FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);
			
			AUndegard_Projectile* CurrentProjectile = GetWorld()->SpawnActor<AUndegard_Projectile>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotation);

			if (IsValid(CurrentProjectile))
			{
				
				if (bDrawLineTrace)
				{
					DrawDebugSphere(GetWorld(), CurrentProjectile->ProjectileLocationAtCollision, 200, 26, FColor::Red,true,-1,0,2);
					UE_LOG(LogTemp, Log, TEXT("Debugging Sphere"));
				}
			}
		}

		
	}
}

void AUndegard_Launcher::StopAction()
{
	Super::StopAction();
}
