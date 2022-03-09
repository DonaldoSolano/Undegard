// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Rifle.h"

void AUndegard_Rifle::StartAction()
{
	Super::StartAction();
	UE_LOG(LogTemp, Log, TEXT("Player starts action!"));
}

void AUndegard_Rifle::StopAction()
{
	Super::StopAction();
	UE_LOG(LogTemp, Log, TEXT("Player stops action!"));
}
