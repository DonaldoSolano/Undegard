// Fill out your copyright notice in the Description page of Project Settings.


#include "Music/Undegard_LevelMusic.h"
#include "Components/AudioComponent.h"
#include "Components/BillboardComponent.h"
#include "Core/Undegard_GameMode.h"

// Sets default values
AUndegard_LevelMusic::AUndegard_LevelMusic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MusicBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("MusicBillboardComponent"));
	RootComponent = MusicBillboardComponent;

	MusicAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent"));
	MusicAudioComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AUndegard_LevelMusic::BeginPlay()
{
	Super::BeginPlay();
	GameModeReference = Cast<AUndegard_GameMode>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameModeReference))
	{
		GameModeReference->OnVictoryDelegate.AddDynamic(this, &AUndegard_LevelMusic::StopLevelMusic);
		GameModeReference->OnGameOverDelegate.AddDynamic(this, &AUndegard_LevelMusic::StopLevelMusic);
	}
}

void AUndegard_LevelMusic::StopLevelMusic()
{
	MusicAudioComponent->Stop();
}

// Called every frame
void AUndegard_LevelMusic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

