// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Undegard_AIController.h"
#include "AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Undegard/Public/Enemy/Undegard_Enemy.h"


AUndegard_AIController::AUndegard_AIController() {

}

void AUndegard_AIController::BeginPlay() {
	Super::BeginPlay();

	if (IsValid(EnemyBehaviorTree))
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}

	MyEnemy = Cast<AUndegard_Enemy>(K2_GetPawn());

	if (IsValid(MyEnemy))
	{

	}
}
