// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Undegard_Weapon.h"
#include "Undegard_Rifle.generated.h"

class UParticleSystem;
/**
 * 
 */
UCLASS()
class UNDEGARD_API AUndegard_Rifle : public AUndegard_Weapon
{
	GENERATED_BODY()

public:
	AUndegard_Rifle();
	
protected:
	virtual void StartAction() override;
	
	virtual	void StopAction() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace")
	float TraceLenght;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace|Debug")
	bool bDrawLineTrace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* TraceEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName TraceParamName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timers")
	FTimerHandle MemberTimerHandle;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shoot Mode")
	bool bIsAutomaticShootActivated;
};
