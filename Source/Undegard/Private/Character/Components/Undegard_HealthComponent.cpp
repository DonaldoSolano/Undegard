// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/Undegard_HealthComponent.h"

// Sets default values for this component's properties
UUndegard_HealthComponent::UUndegard_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
}


// Called when the game starts
void UUndegard_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	MyOwner = GetOwner();

	if (IsValid(MyOwner))
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UUndegard_HealthComponent::TakeDamage);

	}
	
}


// Called every frame
void UUndegard_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUndegard_HealthComponent::TakeDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	UE_LOG(LogTemp, Log, TEXT("My Health is: %s"), *FString::SanitizeFloat(CurrentHealth));
}

