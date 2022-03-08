// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Undegard_Activator.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class AUndegard_Character;
class AUndegard_Launchpad;

UCLASS()
class UNDEGARD_API AUndegard_Activator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUndegard_Activator();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ActivatorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* ActivatorColliderComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckIfPlayerColliding(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Activator")
	void BP_LaunchpadActivated();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Activator")
	void BP_ChangeLaunchpadColor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchpadActivated();
};
