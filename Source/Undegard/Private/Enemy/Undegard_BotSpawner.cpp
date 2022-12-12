// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Undegard_BotSpawner.h"
#include "Components/BillboardComponent.h"
#include "Enemy/Undegard_Bot.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AUndegard_BotSpawner::AUndegard_BotSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnerBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("SpawnerBillboard"));
	RootComponent = SpawnerBillboardComponent;
	bIsActive = true;
	MaxBotsCounter = 1;
	TimeToSpawn = 1.0f;
}

// Called when the game starts or when spawned
void AUndegard_BotSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandleSpawnBot, this, &AUndegard_BotSpawner::SpawnBot, TimeToSpawn, true);
}

void AUndegard_BotSpawner::SpawnBot()
{
	if (!bIsActive)
	{
		return;
	}

	if (CurrentBotsCounter>=MaxBotsCounter)
	{
		return;
	}

	if (IsValid(BotClass))
	{
		//When dealing with spawn locations we always have to transform from local to global.
		FVector LocalSpawnPoint = GetSpawnPoint();
		FVector GlobalSpawnPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(),LocalSpawnPoint);
		FActorSpawnParameters SpawnParameters;

		/*---------------------------------------------------------------------------------------------------------------------*/
		//Traditional way of spawning:
		//SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		//SpawnActor<AUndegard_Bot>(BotClass, SpawnPoint, FRotator::ZeroRotator);
		/*---------------------------------------------------------------------------------------------------------------------*/

		//This is the deferred way:
		FTransform BotTransform = FTransform(FRotator::ZeroRotator, GlobalSpawnPoint);
		AUndegard_Bot* NewBot = GetWorld()->SpawnActorDeferred<AUndegard_Bot>(BotClass, BotTransform);

		if (IsValid(NewBot))
		{
			NewBot->SetSpawner(this);
		}

		NewBot->FinishSpawning(BotTransform);

		CurrentBotsCounter++;
	}
}

FVector AUndegard_BotSpawner::GetSpawnPoint()
{
	if (SpawnPoints.Num()>0)
	{
		int IndexSelected = FMath::RandRange(0, SpawnPoints.Num() - 1);
		return SpawnPoints[IndexSelected];
	}
	else
	{
		return GetActorLocation();
	}
	
}

void AUndegard_BotSpawner::NotifyBotDead()
{
	CurrentBotsCounter--;
}

// Called every frame
void AUndegard_BotSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

