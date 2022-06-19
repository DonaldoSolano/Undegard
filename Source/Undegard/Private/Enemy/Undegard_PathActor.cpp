// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Undegard_PathActor.h"
#include "Components/BillboardComponent.h"

// Sets default values
AUndegard_PathActor::AUndegard_PathActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PathBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("PathBillboard"));
	RootComponent = PathBillboardComponent;
}

// Called when the game starts or when spawned
void AUndegard_PathActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUndegard_PathActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

