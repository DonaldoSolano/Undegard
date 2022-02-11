// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Door.h"

// Sets default values
AUndegard_Door::AUndegard_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	openAngle = -90.0f;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameComponent->SetupAttachment(CustomRootComponent);

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorComponent->SetupAttachment(CustomRootComponent);
}

// Called when the game starts or when spawned
void AUndegard_Door::BeginPlay()
{
	Super::BeginPlay();
	OpenDoor();
}

// Called every frame
void AUndegard_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUndegard_Door::OpenDoor()
{
	FRotator newRotation = FRotator(0.0f, openAngle, 0.0f);
	DoorComponent->SetRelativeRotation(newRotation);
}

