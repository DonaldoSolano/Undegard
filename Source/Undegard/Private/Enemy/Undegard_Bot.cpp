// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Undegard_Bot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Undegard_Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "Character/Components/Undegard_HealthComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Particles/ParticleSystem.h"
#include "Undegard_Rifle.h"
#include "Items/Undegard_Item.h"
#include "Undegard_Rifle.h"
#include "Enemy/Undegard_BotSpawner.h"

// Sets default values
AUndegard_Bot::AUndegard_Bot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BotMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bot mesh component"));
	BotMeshComponent->SetCanEverAffectNavigation(false);
	BotMeshComponent->SetSimulatePhysics(true);
	RootComponent = BotMeshComponent;

	Hitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));

	Hitbox->SetupAttachment(RootComponent);

	Hitbox->SetCollisionResponseToAllChannels(ECR_Ignore);
	Hitbox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Hitbox->SetSphereRadius(150.0f);


	HealthComponent = CreateDefaultSubobject<UUndegard_HealthComponent>(TEXT("HealthComponent"));

	MinDistanceToTarget = 100.0f;

	MagnitudeForce = 500.0f;

	ExplosionDamage = 100.0f;
	ExplotionRadius = 50.0f;

	XPValue = 15.0f;

	LootProbability = 100.0f;

	bDebug = false;
}

// Called when the game starts or when spawned
void AUndegard_Bot::BeginPlay()
{
	Super::BeginPlay();

	BotMaterial = BotMeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BotMeshComponent->GetMaterial(0));

	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &AUndegard_Bot::StartCountDown);

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AUndegard_Bot::OnHealthChange);

	HealthComponent->OnDeadDelegate.AddDynamic(this, &AUndegard_Bot::GiveXP);

	//Get the player reference and then verify if the pawn is a player character.
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (IsValid(PlayerPawn))
	{
		PlayerCharacter = Cast<AUndegard_Character>(PlayerPawn);
	}

	//Get the first nav mesh bot path point.
	NextPathPoint = GetNextPathPoint();
}

FVector AUndegard_Bot::GetNextPathPoint()
{
	if (!IsValid(PlayerCharacter))
	{
		return GetActorLocation();
	}

	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), GetActorLocation(), PlayerCharacter);
	if (NavigationPath->PathPoints.Num() > 1)
	{
		return NavigationPath->PathPoints[1];
	}

	//If navigation points are less or equal than 1.
	return FVector();
}

void AUndegard_Bot::OnHealthChange(UUndegard_HealthComponent * CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (IsValid(BotMaterial))
	{
		BotMaterial->SetScalarParameterValue("Pulse", GetWorld()->TimeSeconds);
	}

	if (CurrentHealthComponent->IsDead())
	{
		if (IsValid(DamageCauser))
		{
			AUndegard_Rifle* CharacterCauser = Cast<AUndegard_Rifle>(DamageCauser);
			if (IsValid(CharacterCauser))
			{
				TrySpawnLoot();
			}
		}
		SelfDestruction();
	}
}

void AUndegard_Bot::StartCountDown(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsStartingCountdown)
	{
		return;
	}

	if (OtherActor == PlayerCharacter)
	{
		bIsStartingCountdown = true;

		GetWorld()->GetTimerManager().SetTimer(CountdownTime, this, &AUndegard_Bot::SelfDamage, 0.5f, true);
	}
}

void AUndegard_Bot::SelfDestruction()
{
	if (bIsExploded)
	{
		return;
	}

	bIsExploded = true;

	if (IsValid(ExplosionEffect))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	}
	
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionDamage, GetActorLocation(), ExplotionRadius, nullptr, IgnoredActors, this, GetInstigatorController(), true);

	if (IsValid(MySpawner))
	{
		MySpawner->NotifyBotDead();
	}

	Destroy();
}

void AUndegard_Bot::SelfDamage()
{
	UGameplayStatics::ApplyDamage(this,20.0f, GetInstigatorController(), nullptr, nullptr);
}

void AUndegard_Bot::GiveXP(AActor * DamageCauser)
{
	AUndegard_Character* Player = Cast<AUndegard_Character>(DamageCauser);

	if (IsValid(Player) && Player->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
	{
		Player->GainUltimateXP(XPValue);
	}

	AUndegard_Rifle* Rifle = Cast<AUndegard_Rifle>(DamageCauser);
	if (IsValid(Rifle))
	{
		AUndegard_Character* RifleOwner = Cast<AUndegard_Character>(Rifle->GetOwner());
		if (IsValid(RifleOwner) && RifleOwner->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
		{
			RifleOwner->GainUltimateXP(XPValue);
		}
	}

	BP_GiveXP(DamageCauser);
}

bool AUndegard_Bot::TrySpawnLoot()
{
	if (!IsValid(LootItemClass))
	{
		return false;
	}

	float SelectedProbability = FMath::RandRange(0.0f, 100.0f);

	if (SelectedProbability <= LootProbability)
	{
		//Create the parameters structure object.
		FActorSpawnParameters SpawnParameters;

		//Spawn the object event if there is a collision on that point.
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//Spawn the object.
		GetWorld()->SpawnActor<AUndegard_Item>(LootItemClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);
	}

	return true;
}

// Called every frame
void AUndegard_Bot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Finding the distance between the player and the bot, if the distance is less than the minimum, move the bot to the next path point.
	float DistanceToTarget = (GetActorLocation()-NextPathPoint).Size();
	if (DistanceToTarget <= MinDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();
	}
	else
	{
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= MagnitudeForce;

		BotMeshComponent->AddForce(ForceDirection, NAME_None, true);
	}

	if (bDebug)
	{
		//
	}
}

