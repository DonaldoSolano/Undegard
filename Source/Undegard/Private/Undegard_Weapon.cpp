// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Weapon.h"

// Sets default values
AUndegard_Weapon::AUndegard_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUndegard_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUndegard_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUndegard_Weapon::StartAction()
{
	BP_StartAction();
}

void AUndegard_Weapon::StopAction()
{
	BP_StopAction();
}

