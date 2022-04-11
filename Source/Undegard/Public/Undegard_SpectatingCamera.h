// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Undegard_SpectatingCamera.generated.h"

class UStaticMeshComponent;

UENUM(Blueprintable)
enum class EUndegard_SpectatingCameraType : uint8
{
	CameraType_None UMETA(DisplayName = "None"),
	CameraType_Victory UMETA(DisplayName = "Victory"),
	CameraType_GameOver UMETA(DisplayName = "Game Over")
};

UCLASS()
class UNDEGARD_API AUndegard_SpectatingCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUndegard_SpectatingCamera();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpectatingCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spectating Camera")
	EUndegard_SpectatingCameraType CameraType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EUndegard_SpectatingCameraType GetCameraType() { return CameraType; };
};
