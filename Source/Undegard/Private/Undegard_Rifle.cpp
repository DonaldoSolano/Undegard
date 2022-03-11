// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Rifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"

AUndegard_Rifle::AUndegard_Rifle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TraceLenght = 10000.0f;
	MuzzleSocketName = "SCK_Muzzle";
}

void AUndegard_Rifle::StartAction()
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
		FVector TraceEnd = EyeLocation + (ShotDirection * TraceLenght);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(CurrentOwner);
		QueryParams.bTraceComplex = true;

		FVector TraceEndPoint = TraceEnd;

		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, TraceEnd, ECC_Visibility, QueryParams);

		if (bHit)
		{
			// Make damage
			AActor* HitActor = HitResult.GetActor();
			if (IsValid(HitActor))
			{
				//If the argument of the method is preceeded with an 'const &...' it means that it is not a outgoing argument but just an indication 
				//for the compiler to work with the original argument content and don't work with a duplicate of it. 
				UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShotDirection, HitResult, CurrentOwner->GetInstigatorController(),this, DamageType);
			}

			if (IsValid(ImpactEffect))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,HitResult.ImpactPoint, HitResult.Normal.Rotation());
			}

			TraceEndPoint = HitResult.ImpactPoint;
		}

		if (bDrawLineTrace)
		{
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.0f, 0.0f, 1.0f);
		}

		if (IsValid(MuzzleEffect))
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, CurrentOwnerCharacter->GetMesh(),MuzzleSocketName);
		}

		if (IsValid(TraceEffect))
		{
			USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();

			if (IsValid(CharacterMeshComponent))
			{
				FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
				UParticleSystemComponent* TraceComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, MuzzleSocketLocation);

				if (IsValid(TraceComponent))
				{
					TraceComponent->SetVectorParameter(TraceParamName, TraceEndPoint);
				}
			}
		}
	}
}

void AUndegard_Rifle::StopAction()
{
	Super::StopAction();
	
}

//UE_LOG(LogTemp, Log, TEXT("Player stops action!"));
