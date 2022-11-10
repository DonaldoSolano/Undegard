// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy/Undegard_BotSpawner.h"

class UBillboardComponent;
class AUndegard_Bot;
UCLASS()
class UNDEGARD_API AUndegard_BotSpawner : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Billboard")
	UBillboardComponent* SpawnerBillboardComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (UIMin = 1.0, ClampMin = 1.0))
	int MaxBotsCounter;

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
	int CurrentBotsCounter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawner")
	TSubclassOf<AUndegard_Bot*> BotClass;

	FTimerHandle TimerHandleSpawnBot;

public:	
	// Sets default values for this actor's properties
	AUndegard_BotSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
