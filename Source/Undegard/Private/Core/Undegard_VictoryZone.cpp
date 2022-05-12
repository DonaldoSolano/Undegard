// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Undegard_VictoryZone.h"
#include "Components/BoxComponent.h"
#include "Undegard_Character.h"
#include "Core/Undegard_GameMode.h"

// Sets default values
AUndegard_VictoryZone::AUndegard_VictoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VictoryZoneComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VictoryZoneComponent"));
	RootComponent = VictoryZoneComponent;
	VictoryZoneComponent->SetBoxExtent(FVector(100.0f));
}

// Called when the game starts or when spawned
void AUndegard_VictoryZone::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeReference = Cast<AUndegard_GameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AUndegard_VictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUndegard_VictoryZone::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (IsValid(OtherActor) && IsValid(GameModeReference))
	{
		AUndegard_Character* UndegardCharacter = Cast<AUndegard_Character>(OtherActor);

		if (IsValid(UndegardCharacter) && UndegardCharacter->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
		{
			GameModeReference->Victory(UndegardCharacter);
		}
	}
}

