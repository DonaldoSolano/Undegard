// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Undegard_Item.generated.h"

class USphereComponent;
class AUndegard_Character;
class AUndegard_GameMode;
class USoundCue;

UCLASS()
class UNDEGARD_API AUndegard_Item : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Components")
	USphereComponent* MainColliderComponent;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Game Mode")
	AUndegard_GameMode* GameModeReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup sfx")
	USoundCue* ItemPickupSoundCue;


public:	
	// Sets default values for this actor's properties
	AUndegard_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Pickup(AUndegard_Character* PickupActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void BP_Pickup(AUndegard_Character* PickupActor);

	void PlayPickupSound(USoundCue* MusicCue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
