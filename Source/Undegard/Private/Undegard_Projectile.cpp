// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AUndegard_Projectile::AUndegard_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	RootComponent = ProjectileCollision;

	ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProjectileCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

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

void AUndegard_Projectile::CheckIfProjectileCollided(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	AActor* HitActor = Hit.GetActor();
	if (IsValid(HitActor))
	{
		ProjectileLocationAtCollision = Hit.Location;
	}
	
}

// Called every frame
void AUndegard_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

