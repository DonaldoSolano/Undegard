// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Undegard_Character.h"
#include "Undegard_Enemy.generated.h"

/**
 * 
 */
class AUndegard_PathActor;
UCLASS()
class UNDEGARD_API AUndegard_Enemy : public AUndegard_Character
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Navigation Path")
	AUndegard_PathActor* PathActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Navigation Path")
	bool bLoopPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Navigation Path")
	int DirectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Navigation Path")
	float WaitingTimeOnPathPoint;

public:
	AUndegard_Enemy();
};
