// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Undegard_Item.h"
#include "Undegard_HealthBox.generated.h"

/**
 * 
 */
class UStaticMeshComponent;
class AUndegard_Character;
UCLASS()
class UNDEGARD_API AUndegard_HealthBox : public AUndegard_Item
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUndegard_HealthBox();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health box|Mesh")
	UStaticMeshComponent* HealthBoxMeshComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health box|Health value")
	float HealthValue;

public:
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetHealthValue() const { return HealthValue; };

protected:
	virtual void Pickup(AUndegard_Character* PickupActor) override;
};
