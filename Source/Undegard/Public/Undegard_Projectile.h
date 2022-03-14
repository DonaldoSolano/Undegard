// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Undegard_Projectile.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class USphereComponent;
class AController;

UCLASS()
class UNDEGARD_API AUndegard_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUndegard_Projectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* ProjectileCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile data")
	FVector ProjectileLocationAtCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile data")
	float ProjectileDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile data")
	AActor* HitActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile data")
	FVector ShotDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile data")
	FHitResult ProjectileHitResult;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile data")
	AController* ControllerInstigator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile data")
	TSubclassOf <UDamageType> ProjectileDamageType;
	

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timers")
	FTimerHandle MemberTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile data")
	TArray <AActor*> ActorsIgnoredOnExplotion;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ExplodeGrenade();

	UFUNCTION()
	void CheckIfProjectileCollided(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
