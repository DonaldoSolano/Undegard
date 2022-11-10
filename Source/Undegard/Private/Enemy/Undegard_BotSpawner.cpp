// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Undegard_BotSpawner.h"
#include "Components/BillboardComponent.h"
#include "Enemy/Undegard_Bot.h"

// Sets default values
AUndegard_BotSpawner::AUndegard_BotSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnerBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("SpawnerBillboard"));
	RootComponent = SpawnerBillboardComponent;
}

// Called when the game starts or when spawned
void AUndegard_BotSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUndegard_BotSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

