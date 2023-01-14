// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Undegard_Bot.generated.h"

class UStaticMeshComponent;
class AUndegard_Character;
class UUndegard_HealthComponent;
class UMaterialInstanceDynamic;
class USphereComponent;
class UParticleSystem;
class AUndegard_Item;
class AUndegard_BotSpawner;
class UUndegard_GameInstance;

UCLASS()
class UNDEGARD_API AUndegard_Bot : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BotMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UUndegard_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* Hitbox;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
	bool bDebug;

	UPROPERTY(BlueprintReadOnly, Category = "Bot Movement")
	bool bIsExploded;

	UPROPERTY(BlueprintReadOnly, Category = "Bot Movement")
	bool bIsStartingCountdown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bot Movement")
	float MinDistanceToTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bot Movement")
	float MagnitudeForce;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bot Damage")
	float ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bot Damage")
	float ExplotionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bot Damage|Time")
	FTimerHandle CountdownTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bot|XP")
	float XPValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot System")
	float LootProbability;

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
	AUndegard_BotSpawner* MySpawner;
	
	UPROPERTY(BlueprintReadOnly, Category = "Bot")
	FVector NextPathPoint;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	AUndegard_Character* PlayerCharacter;

	UMaterialInstanceDynamic* BotMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Effect")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot System")
	TSubclassOf<AUndegard_Item> LootItemClass;

	UUndegard_GameInstance* GameInstanceReference;

public:
	// Sets default values for this pawn's properties
	AUndegard_Bot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	FVector GetNextPathPoint();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void OnHealthChange(UUndegard_HealthComponent * CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void StartCountDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SelfDestruction();

	void SelfDamage();

	UFUNCTION()
	void GiveXP(AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_GiveXP(AActor* DamageCauser);

	UFUNCTION()
	bool TrySpawnLoot();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpawner(AUndegard_BotSpawner* NewSpawner) { MySpawner = NewSpawner; };

	UFUNCTION(BlueprintCallable)
	AUndegard_BotSpawner* GetSpawner() { return MySpawner; };
};
