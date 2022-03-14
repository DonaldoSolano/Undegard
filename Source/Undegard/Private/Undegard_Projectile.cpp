// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework\Controller.h"

// Sets default values
AUndegard_Projectile::AUndegard_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	RootComponent = ProjectileCollision;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(ProjectileCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
}

// Called when the game starts or when spawned
void AUndegard_Projectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileCollision->OnComponentHit.AddDynamic(this, &AUndegard_Projectile::CheckIfProjectileCollided);
}

void AUndegard_Projectile::ExplodeGrenade()
{
	// Make damage
	if (IsValid(HitActor))
	{
		//If the argument of the method is preceeded with an 'const &...' it means that it is not a outgoing argument but just an indication 
		//for the compiler to work with the original argument content and don't work with a duplicate of it. 
		UE_LOG(LogTemp, Log, TEXT("Collision center equals: %f"), ProjectileDamage);
		UGameplayStatics::ApplyRadialDamage(GetWorld(),ProjectileDamage, ProjectileLocationAtCollision, 100.0f, ProjectileDamageType, ActorsIgnoredOnExplotion, this, ControllerInstigator);
	}
	DrawDebugSphere(GetWorld(), ProjectileLocationAtCollision, 100.0f, 26, FColor::Red, true, -1, 0, 2);
	Destroy();
}

void AUndegard_Projectile::CheckIfProjectileCollided(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (IsValid(OtherActor))
	{
		ProjectileLocationAtCollision = Hit.ImpactPoint;
		HitActor = Hit.GetActor();
		ProjectileHitResult = Hit;
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AUndegard_Projectile::ExplodeGrenade, 1.0f, false, 3.0f);
	}
	
}

// Called every frame
void AUndegard_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

