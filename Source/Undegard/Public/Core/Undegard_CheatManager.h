// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "Undegard_CheatManager.generated.h"

/**
 * 
 */
UCLASS()
class UNDEGARD_API UUndegard_CheatManager : public UCheatManager
{
	GENERATED_BODY()
	

public:
	UFUNCTION(exec)
	void Undegard_UltimateReady();
};
