// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Undegard_Weapon.h"
#include "Undegard_Rifle.generated.h"

/**
 * 
 */
UCLASS()
class UNDEGARD_API AUndegard_Rifle : public AUndegard_Weapon
{
	GENERATED_BODY()
	
protected:
	virtual void StartAction() override;
	
	virtual	void StopAction() override;
};
