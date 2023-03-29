// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enemy/Undegard_EnemyHealthBar.h"

void UUndegard_EnemyHealthBar::Updatehealth(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
}
