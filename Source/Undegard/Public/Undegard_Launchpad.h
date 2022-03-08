// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Undegard_Launchpad.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class AUndegard_Character;
class UMaterialInstanceDynamic;

UCLASS()
class UNDEGARD_API AUndegard_Launchpad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUndegard_Launchpad();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* LaunchpadComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* LaunchpadColliderComponent;

	UMaterialInstanceDynamic* LaunchpadColorMaterial;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Launchpad")
	float throwForce;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launchpad")
	bool bIsLaunchpadActivated;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckIfPlayerColliding(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Launchpad")
	void BP_ThrowPlayer(AUndegard_Character* PickupActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ThrowPlayer(AUndegard_Character* OverlappedCharacter);

	UFUNCTION(BlueprintCallable, Category = "Launchpad")
	void ChangeLaunchpadColor();
};
