// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_SpectatingCamera.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AUndegard_SpectatingCamera::AUndegard_SpectatingCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpectatingCameraComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpectatingCamera"));
	RootComponent = SpectatingCameraComponent;

}

// Called when the game starts or when spawned
void AUndegard_SpectatingCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUndegard_SpectatingCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

