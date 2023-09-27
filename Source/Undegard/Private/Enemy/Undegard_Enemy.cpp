// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Undegard_Enemy.h"
#include "Enemy/Undegard_PathActor.h"
#include "Character/Components/Undegard_HealthComponent.h"
#include "Undegard_Character.h"
#include "Undegard_Rifle.h"
#include "Items/Undegard_Item.h"
#include "Enemy/Controller/Undegard_AIController.h"
#include "AIModule/Classes/Perception/AISense_Damage.h"
#include "Core/Undegard_GameInstance.h"
#include "Components/WidgetComponent.h"
#include "UI/Enemy/Undegard_EnemyHealthBar.h"
#include "Core/Undegard_GameMode.h"
#include "Components/CapsuleComponent.h"

void AUndegard_Enemy::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AUndegard_Enemy::HealthChanged);
	HealthComponent->OnDeadDelegate.AddDynamic(this, &AUndegard_Enemy::GiveXP);
	MyAIController = Cast<AUndegard_AIController>(GetController());

	UUserWidget* WidgetObject = WidgetHealthBarComponent->GetUserWidgetObject();
	if (IsValid(WidgetObject))
	{
		EnemyHealthBar = Cast<UUndegard_EnemyHealthBar>(WidgetObject);
		if (IsValid(EnemyHealthBar))
		{
			HealthComponent->OnHealthUpdateDelegate.AddDynamic(EnemyHealthBar, &UUndegard_EnemyHealthBar::Updatehealth);
			HideHealthBar();
		}
	}

	EnemyCapsuleComponent = GetCapsuleComponent();
}

void AUndegard_Enemy::GiveXP(AActor * DamageCauser)
{
	AUndegard_Character* Player = Cast<AUndegard_Character>(DamageCauser);

	if (IsValid(Player) && Player->GetCharacterType()==EUndegard_CharacterType::CharacterType_Player)
	{
		Player->GainUltimateXP(XPValue);
	}

	AUndegard_Rifle* Rifle = Cast<AUndegard_Rifle>(DamageCauser);
	if (IsValid(Rifle))
	{
		AUndegard_Character* RifleOwner = Cast<AUndegard_Character>(Rifle->GetOwner());
		if (IsValid(RifleOwner) && RifleOwner->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
		{
			RifleOwner->GainUltimateXP(XPValue);
			TrySpawnLoot();
		}
	}

	BP_GiveXP(DamageCauser);
}

void AUndegard_Enemy::HealthChanged(UUndegard_HealthComponent * CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (!IsValid(MyAIController))
	{
		return;
	}

	if (bIsShowingHealthBar)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HideHealthBar);
	}
	else
	{
		ShowHealthBar();
	}
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideHealthBar, this, &AUndegard_Enemy::HideHealthBar, 1.0f, false);

	if (CurrentHealthComponent->IsDead())
	{

		MyAIController->DeactivateAIPerception();
		MyAIController->UnPossess();
		MyAIController->Destroy();
		
		EnemyCapsuleComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		EnemyCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (IsValid(GameInstanceReference))
		{
			GameInstanceReference->AddDefeatedEnemyCounter();
		}

		SetAlert(false);

		//Hide enemy health bar component visibility if enemy dies.
		HideHealthBar();
	}
	else
	{
		AUndegard_Rifle* Rifle = Cast<AUndegard_Rifle>(DamageCauser);
		if (IsValid(Rifle))
		{
			//To avoid acces to two pointer at the same time the rifle owner reference is stored in an actor variable
			AActor* RifleOwner = Rifle->GetOwner();
			MyAIController->SetReceiveDamage(true);
			UAISense_Damage::ReportDamageEvent(GetWorld(),this, RifleOwner, Damage, RifleOwner->GetActorLocation(), FVector::ZeroVector);
		}
	}
}

bool AUndegard_Enemy::TrySpawnLoot()
{
	if (!IsValid(LootItemClass))
	{
		return false;
	}

	float SelectedProbability = FMath::RandRange(0.0f, 100.0f);

	if (SelectedProbability<=LootProbability)
	{
		//Create the parameters structure object.
		FActorSpawnParameters SpawnParameters;

		//Spawn the object event if there is a collision on that point.
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//Spawn the object.
		GetWorld()->SpawnActor<AUndegard_Item>(LootItemClass,GetActorLocation(),FRotator::ZeroRotator, SpawnParameters);
	}

	return true;
}

void AUndegard_Enemy::ShowHealthBar()
{
	bIsShowingHealthBar = true;
	EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
}

void AUndegard_Enemy::HideHealthBar()
{
	bIsShowingHealthBar = false;
	EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
}

void AUndegard_Enemy::SetAlert(bool bValue)
{
	bIsAlerted = bValue;
	if (IsValid(GameModeReference))
	{
		GameModeReference->CheckAlertMode();
	}
}

AUndegard_Enemy::AUndegard_Enemy() {
	bLoopPath = false;
	DirectionIndex = 1;
	WaitingTimeOnPathPoint = 1.0f;
	XPValue = 15.0f;
	LootProbability = 100.0f;

	WidgetHealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetHealthBarComponent")); 
	WidgetHealthBarComponent->SetupAttachment(RootComponent);
}