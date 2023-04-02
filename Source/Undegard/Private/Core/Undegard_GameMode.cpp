// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Undegard_GameMode.h"
#include "Undegard_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Undegard_SpectatingCamera.h"
#include "Kismet/GameplayStatics.h"

void AUndegard_GameMode::BeginPlay()
{
	Super::BeginPlay();
	SetUpSpectatingCameras();
}

void AUndegard_GameMode::SetUpSpectatingCameras()
{
	TArray<AActor*> SpectatingCameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUndegard_SpectatingCamera::StaticClass(), SpectatingCameraActors);

	if (SpectatingCameraActors.Num() > 0)
	{
		for (AActor* SpectatingActor : SpectatingCameraActors)
		{
			AUndegard_SpectatingCamera* SpectatingCamera = Cast<AUndegard_SpectatingCamera>(SpectatingActor);

			if (IsValid(SpectatingCamera))
			{
				switch (SpectatingCamera->GetCameraType())
				{
				case EUndegard_SpectatingCameraType::CameraType_Victory:
					VictoryCamera = SpectatingCamera;
					break;

				case EUndegard_SpectatingCameraType::CameraType_GameOver:
					GameOverCamera = SpectatingCamera;
					break;

				default:
					break;
				}
			}
		}
	}
}

void AUndegard_GameMode::MoveCameraToSpectatingPoint(AUndegard_SpectatingCamera * SpectatingCamera, AUndegard_Character* Character)
{
	if (!IsValid(Character) || !IsValid(SpectatingCamera))
	{
		return;
	}

	AController* CharacterController = Character->GetController();

	if (IsValid(CharacterController))
	{
		APlayerController* PlayerController = Cast<APlayerController>(CharacterController);

		if (IsValid(PlayerController))
		{
			PlayerController->SetViewTargetWithBlend(SpectatingCamera, SpectatingBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
}

void AUndegard_GameMode::AddKeyToCharacter(AUndegard_Character* KeyOwner, FName KeyTag)
{
	if (IsValid(KeyOwner))
	{
		OnKeyAddedDelegate.Broadcast(KeyTag);
		KeyOwner->AddKey(KeyTag);
	}
}

void AUndegard_GameMode::Victory(AUndegard_Character* Character)
{
	Character->DisableInput(nullptr);

	MoveCameraToSpectatingPoint(VictoryCamera,Character);

	BP_Victory(Character);
}

void AUndegard_GameMode::GameOver(AUndegard_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (Character->HasToDestroy())
	{
		Character->DetachFromControllerPendingDestroy();
		Character->SetLifeSpan(5.0f);
	}
	else
	{
		Character->DisableInput(nullptr);
		MoveCameraToSpectatingPoint(GameOverCamera, Character);
	}
	
	BP_GameOver(Character);
}