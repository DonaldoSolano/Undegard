// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Launchpad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Undegard_Character.h"
#include "Kismet\KismetMathLibrary.h"
#include "Materials\MaterialInstanceDynamic.h"
#include "Materials\MaterialInterface.h"

// Sets default values
AUndegard_Launchpad::AUndegard_Launchpad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsLaunchpadActivated = false;
	
	throwForce = 100.0f;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	LaunchpadComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Launchpad"));
	LaunchpadComponent->SetupAttachment(CustomRootComponent);

	LaunchpadColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchpadCollider"));
	LaunchpadColliderComponent->SetupAttachment(CustomRootComponent);

	LaunchpadColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LaunchpadColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	LaunchpadColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
}

// Called when the game starts or when spawned
void AUndegard_Launchpad::BeginPlay()
{
	Super::BeginPlay();

	LaunchpadColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AUndegard_Launchpad::CheckIfPlayerColliding);

	auto LaunchpadStaticMesh = FindComponentByClass<UStaticMeshComponent>();
	auto LaunchpadMaterial = LaunchpadStaticMesh->GetMaterial(0);

	LaunchpadColorMaterial = UMaterialInstanceDynamic::Create(LaunchpadMaterial, NULL);

	LaunchpadStaticMesh->SetMaterial(0, LaunchpadColorMaterial);

	ChangeLaunchpadColor();
}

// Called every frame
void AUndegard_Launchpad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUndegard_Launchpad::CheckIfPlayerColliding(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsLaunchpadActivated == false)
	{
		return;
	}

	if (IsValid(OtherActor))
	{
		AUndegard_Character* OverlappedCharacter = Cast<AUndegard_Character>(OtherActor);
		if (IsValid(OverlappedCharacter) && OverlappedCharacter->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
		{
			BP_ThrowPlayer(OverlappedCharacter);
			ThrowPlayer(OverlappedCharacter);
		}
	}
}

void AUndegard_Launchpad::ThrowPlayer(AUndegard_Character* OverlappedCharacter)
{
	FVector upDirection = UKismetMathLibrary::GetUpVector(GetActorRotation())*throwForce;
	OverlappedCharacter->LaunchCharacter(upDirection,true,true);
}

void AUndegard_Launchpad::ChangeLaunchpadColor()
{
	LaunchpadColorMaterial->SetScalarParameterValue(TEXT("Blend"), bIsLaunchpadActivated ? 0.0f : 1.0f);
}


