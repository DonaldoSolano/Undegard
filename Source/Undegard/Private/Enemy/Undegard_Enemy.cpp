// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Undegard_Enemy.h"
#include "Enemy/Undegard_PathActor.h"

AUndegard_Enemy::AUndegard_Enemy() {
	bLoopPath = false;
	DirectionIndex = 1;
	WaitingTimeOnPathPoint = 1.0f;
}