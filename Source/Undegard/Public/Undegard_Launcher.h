// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Undegard_Weapon.h"
#include "Undegard_Launcher.generated.h"

class AUndegard_Projectile;

UCLASS()
class UNDEGARD_API AUndegard_Launcher : public AUndegard_Weapon
{
	GENERATED_BODY()

public:
	AUndegard_Launcher();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grenade Launcher")
	TSubclassOf<AUndegard_Projectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName MuzzleSocketName;
	
protected:
	virtual void StartAction() override;

	virtual	void StopAction() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace|Debug")
	bool bDrawLineTrace;
};
