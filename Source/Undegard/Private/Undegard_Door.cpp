// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Undegard_Character.h"

// Sets default values
AUndegard_Door::AUndegard_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	openAngle = -90.0f;

	DoorTag = "KeyA";

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameComponent->SetupAttachment(CustomRootComponent);

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorComponent->SetupAttachment(CustomRootComponent);

	KeyZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyZoneCollider"));
	KeyZoneColliderComponent->SetupAttachment(CustomRootComponent);

	KeyZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeyZoneColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	KeyZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AUndegard_Door::BeginPlay()
{
	Super::BeginPlay();
	KeyZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AUndegard_Door::CheckKeyFromPlayer);
}

void AUndegard_Door::CheckKeyFromPlayer(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor))
	{
		AUndegard_Character* OverlappedCharacter = Cast<AUndegard_Character>(OtherActor);
		if (IsValid(OverlappedCharacter))
		{
			if (OverlappedCharacter->HasKey(DoorTag))
			{
				OpenDoor();
			}
		}
	}
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

