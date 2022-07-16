// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Undegard_Bot.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AUndegard_Bot::AUndegard_Bot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BotMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bot mesh component"));
	BotMeshComponent->SetCanEverAffectNavigation(false);
	RootComponent = BotMeshComponent;
}

// Called when the game starts or when spawned
void AUndegard_Bot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUndegard_Bot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

