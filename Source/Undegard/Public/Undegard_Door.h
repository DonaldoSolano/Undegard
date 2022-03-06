// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Undegard_Door.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class AUndegard_Character;

UCLASS()
class UNDEGARD_API AUndegard_Door : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorFrameComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* KeyZoneColliderComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	float openAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	bool bIsOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	FName DoorTag;

public:	
	// Sets default values for this actor's properties
	AUndegard_Door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Door")
	void BP_OpenDoor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenDoor();
};
