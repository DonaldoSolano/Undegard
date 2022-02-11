// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Undegard_Platform.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class UNDEGARD_API AUndegard_Platform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUndegard_Platform();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* platformMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* CustomRootComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform");
	bool bIsGoingUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform");
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform");
	float minHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform");
	float maxHeight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
