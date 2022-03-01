// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Undegard_Item.h"
#include "Udegard_DoorKey.generated.h"

/**
 * 
 */
class UStaticMeshComponent;
class AUndegard_Character;
UCLASS()
class UNDEGARD_API AUdegard_DoorKey : public AUndegard_Item
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AUdegard_DoorKey();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* KeyMeshComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
	FName KeyTag;

public:
	UFUNCTION(BlueprintCallable, Category = "Getter")
	FName GetKeyTag() const { return KeyTag; };

protected:
	virtual void Pickup(AUndegard_Character* PickupActor) override;
};
