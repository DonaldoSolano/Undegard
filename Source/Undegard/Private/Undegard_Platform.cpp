// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Platform.h"
#include "Kismet\KismetMathLibrary.h"

// Sets default values
AUndegard_Platform::AUndegard_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	platformMeshComponent = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	platformMeshComponent->SetupAttachment(CustomRootComponent);

	bIsGoingUp = true;
	speed = 10.0f;
	minHeight = 0.0f;
	maxHeight = 50.0f;
}

// Called when the game starts or when spawned
void AUndegard_Platform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUndegard_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AUndegard_Platform::Move()
{
	FVector upDirection = UKismetMathLibrary::GetUpVector(GetActorRotation());

	if (bIsGoingUp)
	{
		upDirection = upDirection;
	} 
	else
	{
		upDirection *= -1;
	}

	const FVector currentVelocity = upDirection * speed;
	const FVector newPosition = GetActorLocation() + currentVelocity;
	SetActorLocation(newPosition);

	if ((bIsGoingUp && GetActorLocation().Z >= maxHeight)||(!bIsGoingUp && GetActorLocation().Z <= minHeight))
	{
		bIsGoingUp = !bIsGoingUp;
	}
}
