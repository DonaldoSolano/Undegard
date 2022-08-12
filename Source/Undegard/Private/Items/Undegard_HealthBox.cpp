// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Undegard_HealthBox.h"
#include "Undegard_Character.h"
#include "Components/StaticMeshComponent.h"

AUndegard_HealthBox::AUndegard_HealthBox()
{
	HealthBoxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	HealthBoxMeshComponent->SetupAttachment(RootComponent);
	HealthBoxMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthValue = 30.0f;
}

void AUndegard_HealthBox::Pickup(AUndegard_Character* PickupActor)
{
	Super::Pickup(PickupActor);

	PickupActor->AddHealth(HealthValue);

	Destroy();
}
