// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Undegard_Item.h"
#include "Components/SphereComponent.h"
#include "Undegard_Character.h"
#include "Core/Undegard_GameMode.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUndegard_Item::AUndegard_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	RootComponent = MainColliderComponent;
	MainColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AUndegard_Item::BeginPlay()
{
	Super::BeginPlay();
	GameModeReference = Cast<AUndegard_GameMode>(GetWorld()->GetAuthGameMode());
}

void AUndegard_Item::PlayPickupSound(USoundCue* MusicCue)
{
	if (!IsValid(MusicCue))
	{
		return;
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), MusicCue);
	}
}

// Called every frame
void AUndegard_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUndegard_Item::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor))
	{
		AUndegard_Character* OverlappedCharacter = Cast<AUndegard_Character>(OtherActor);
		if (IsValid(OverlappedCharacter) && OverlappedCharacter->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
		{
			PlayPickupSound(ItemPickupSoundCue);
			Pickup(OverlappedCharacter);
		}
	}
}

void AUndegard_Item::Pickup(AUndegard_Character* PickupActor)
{
	BP_Pickup(PickupActor);
}

