// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Undegard_PathActor.generated.h"

class UBillboardComponent;
UCLASS()
class UNDEGARD_API AUndegard_PathActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUndegard_PathActor();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path", meta = (MakeEditWidget = true))
	TArray<FVector> PathPoints;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Billboard")
	UBillboardComponent* PathBillboardComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
