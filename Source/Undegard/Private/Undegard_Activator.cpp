// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Activator.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Undegard_Character.h"
#include "Undegard_Launchpad.h"

// Sets default values
AUndegard_Activator::AUndegard_Activator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	ActivatorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Activator"));
	ActivatorComponent->SetupAttachment(CustomRootComponent);

	ActivatorColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivatorCollider"));
	ActivatorColliderComponent->SetupAttachment(CustomRootComponent);

	ActivatorColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivatorColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ActivatorColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AUndegard_Activator::BeginPlay()
{
	Super::BeginPlay();

	ActivatorColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AUndegard_Activator::CheckIfPlayerColliding);
}

// Called every frame
void AUndegard_Activator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUndegard_Activator::CheckIfPlayerColliding(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor))
	{
		AUndegard_Character* OverlappedCharacter = Cast<AUndegard_Character>(OtherActor);
		
		if (IsValid(OverlappedCharacter))
		{
			LaunchpadActivated();
		}
	}
}

void AUndegard_Activator::LaunchpadActivated()
{
	BP_LaunchpadActivated();
	BP_ChangeLaunchpadColor();
}

