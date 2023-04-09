// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Undegard_LevelMusic.generated.h"

class UAudioComponent;
class UBillboardComponent;
class AUndegard_GameMode;

UCLASS()
class UNDEGARD_API AUndegard_LevelMusic : public AActor
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAudioComponent* MusicAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBillboardComponent* MusicBillboardComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music")
	FName AlertParamName;


	UPROPERTY(BlueprintReadOnly, Category = "References")
	AUndegard_GameMode* GameModeReference;

public:	
	// Sets default values for this actor's properties
	AUndegard_LevelMusic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void StopLevelMusic();

	UFUNCTION()
	void ChangeLevelMusic(bool bIsAlert);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
