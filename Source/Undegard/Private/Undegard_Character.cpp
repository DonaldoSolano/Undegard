// Fill out your copyright notice in the Description page of Project Settings.

#include "Undegard/Undegard.h"
#include "Undegard_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Undegard_Weapon.h"
#include "Undegard_Rifle.h"
#include "Character/Components/Undegard_HealthComponent.h"
#include "Core/Undegard_GameMode.h"
#include "Core/Undegard_GameInstance.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AUndegard_Character::AUndegard_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseFirstPersonView = true;

	bIsSprinting = false;

	MaxComboMultiplier = 4.0f;

	CurrentComboMultiplier = 1.0f;

	FPSCameraSocketName = "SCK_Camera";
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(GetMesh(), FPSCameraSocketName);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	TPSCameraSocketName = "TCK_Camera";
	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);

	MeleeSocketName = "SCK_Melee";
	MeleeDetectorComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeDetectorComponent"));
	MeleeDetectorComponent->SetupAttachment(GetMesh(), MeleeSocketName);
	MeleeDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeDetectorComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	MeleeDetectorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MainMenuMapName = "MainMenuMap";

	MeleeDamage = 10.0f;

	HealthComponent = CreateDefaultSubobject<UUndegard_HealthComponent>(TEXT("HealthComponent"));

	StepSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("StepSoundComponent"));
	StepSoundComponent->SetupAttachment(RootComponent);

	VoiceSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("VoiceSoundComponent"));
	VoiceSoundComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AUndegard_Character::BeginPlay()
{
	Super::BeginPlay();
	CreateInitialWeapon();
	InitializeReferences();

	MaxUltimateXP = 100.0f;

	MeleeDetectorComponent->OnComponentBeginOverlap.AddDynamic(this,&AUndegard_Character::MakeMeleeDamage);

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AUndegard_Character::OnHealthChange);

	bCanCharacterUseWeapon = true;
}

void AUndegard_Character::InitializeReferences()
{
	if (IsValid(GetMesh()))
	{
		AnimInstance = GetMesh()->GetAnimInstance();
	}

	GameModeReference = Cast<AUndegard_GameMode>(GetWorld()->GetAuthGameMode());
	GameInstanceReference = Cast<UUndegard_GameInstance>(GetWorld()->GetGameInstance());
}

// Called every frame
void AUndegard_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUndegard_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUndegard_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUndegard_Character::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AUndegard_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &AUndegard_Character::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AUndegard_Character::Jump);
	PlayerInputComponent->BindAction("StopJumping", IE_Released, this, &AUndegard_Character::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AUndegard_Character::Sprint);

	PlayerInputComponent->BindAction("WeaponAction", IE_Pressed, this, &AUndegard_Character::StartWeaponAction);

	PlayerInputComponent->BindAction("WeaponAction", IE_Released, this, &AUndegard_Character::StopWeaponAction);

	PlayerInputComponent->BindAction("SwitchRifleMode", IE_Pressed, this, &AUndegard_Character::SwitchWeaponMode);

	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &AUndegard_Character::StartMelee);
	PlayerInputComponent->BindAction("Melee", IE_Released, this, &AUndegard_Character::StopMelee);

	PlayerInputComponent->BindAction("Ultimate", IE_Pressed, this, &AUndegard_Character::StartUltimate);
	PlayerInputComponent->BindAction("Ultimate", IE_Released, this, &AUndegard_Character::StopUltimate);

	PlayerInputComponent->BindAction("Exit", IE_Pressed, this, &AUndegard_Character::GoToMainMenu);
}

void AUndegard_Character::StartMelee()
{
	if (bIsDoingMelee && !bCanMakeCombos)
	{
		return;
	}

	if (bCanMakeCombos)
	{
		if (bIsDoingMelee)
		{
			if (bIsComboEnabled)
			{
				if (CurrentComboMultiplier < MaxComboMultiplier)
				{
					CurrentComboMultiplier++;
					SetComboEnabled(false);
				}
			}
			else
			{
				return;
			}
		}
	}

	if (IsValid(AnimInstance) && IsValid(MeleeMontage[0]))
	{
		switch (int(CurrentComboMultiplier))
		{
		case 1:
			UE_LOG(LogTemp, Warning, TEXT("Player starts melee action 0"));
			AnimInstance->Montage_Play(MeleeMontage[0]);
			break;

		case 2:
			UE_LOG(LogTemp, Warning, TEXT("Player starts melee action 1"));
			AnimInstance->Montage_Play(MeleeMontage[1]);
			break;
		default:
			break;
		}
		
	}
	SetActionsState(true);
}

void AUndegard_Character::StopMelee() 
{
	UE_LOG(LogTemp, Warning, TEXT("Player stops melee action"));
}

void AUndegard_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

void AUndegard_Character::AddHealth(float HealthToAdd)
{
	HealthComponent->AddHealth(HealthToAdd);
}

bool AUndegard_Character::HasKey(FName KeyTag)
{
	return DoorKeys.Contains(KeyTag);
}

void AUndegard_Character::SetActionsState(bool NewState)
{
	bIsDoingMelee = NewState;
	bCanCharacterUseWeapon = !NewState;
}

void AUndegard_Character::SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState)
{
	MeleeDetectorComponent->SetCollisionEnabled(NewCollisionState);
}

void AUndegard_Character::MakeMeleeDamage(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor == this)
		{
			return;
		}

		AUndegard_Character* MeleeTarget = Cast<AUndegard_Character>(OtherActor);

		if (IsValid(MeleeTarget))
		{
			bool bPlayerAttackingEnemy = GetCharacterType() == EUndegard_CharacterType::CharacterType_Player && MeleeTarget->GetCharacterType() == EUndegard_CharacterType::CharacterType_Enemy;
			bool bEnemyAttackingPlayer = GetCharacterType() == EUndegard_CharacterType::CharacterType_Enemy && MeleeTarget->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player;

			if (bPlayerAttackingEnemy || bEnemyAttackingPlayer)
			{
				//const FHitResult & SweepResult in this case works as an argument we can retrieve info from because of the const + &.
				UGameplayStatics::ApplyPointDamage(OtherActor, MeleeDamage * CurrentComboMultiplier, SweepResult.Location, SweepResult, GetInstigatorController(), this, nullptr);
			}
		}
	}
}

void AUndegard_Character::OnHealthChange(UUndegard_HealthComponent * CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (!HealthComponent->IsDead())
	{
		PlayVoiceSound(HurtSound);
	}

	if (HealthComponent->IsDead() && GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
	{
		PlayVoiceSound(DeadSound);

		if (IsValid(GameModeReference))
		{
			GameModeReference->GameOver(this);
		}
	}
}

void AUndegard_Character::SetComboEnabled(bool NewState)
{
	bIsComboEnabled = NewState;
}

void AUndegard_Character::ResetCombo()
{
	SetComboEnabled(false);
	CurrentComboMultiplier = 1.0f;
}

void AUndegard_Character::GainUltimateXP(float XPGained)
{
	if (bCanUseUltimate || bIsUsingUltimate)
	{
		return;
	}

	CurrentUltimateXP = FMath::Clamp(CurrentUltimateXP + XPGained, 0.0f, MaxUltimateXP);
	OnUltimateUpdateDelegate.Broadcast(CurrentUltimateXP, MaxUltimateXP);

	if (CurrentUltimateXP == MaxUltimateXP)
	{
		bCanUseUltimate = true;
		OnUltimateStatusDelegate.Broadcast(bCanUseUltimate);
	}

	BP_GainUltimateXP(XPGained);
}

void AUndegard_Character::StartUltimate()
{
	if (bCanUseUltimate && !bIsUsingUltimate)
	{
		BP_StartUltimate();
		bIsUsingUltimate = true;

		PlayVoiceSound(UltimateSound);
	}
}

void AUndegard_Character::UpdateUltimateDuration(float Value)
{
	CurrentUltimateDuration = FMath::Clamp(CurrentUltimateDuration - Value, 0.0f, MaxUltimateDuration);
	OnUltimateUpdateDelegate.Broadcast(CurrentUltimateDuration, MaxUltimateDuration);
	BP_UltimateDuration(Value);

	if (CurrentUltimateDuration == 0.0f)
	{
		bIsUsingUltimate = false;
		CurrentUltimateXP = 0.0f;
		OnUltimateStatusDelegate.Broadcast(bCanUseUltimate);
		//GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;
		//PlayRate = 1.0f;
		//if(!bUltimateWithTick)
		//{
		//	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Ultimate);
		//}
		BP_StopUltimate();
	}
}

void AUndegard_Character::UpdateUltimateDurationWithTimer()
{
	//UpdateUltimateDuration(UltimateFrecuency);
}

void AUndegard_Character::StopUltimate()
{
}

void AUndegard_Character::GoToMainMenu()
{

	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->SaveData();
	}
	UGameplayStatics::OpenLevel(GetWorld(),MainMenuMapName);
}

void AUndegard_Character::PlayStepSound()
{
	StepSoundComponent->Play();
}

void AUndegard_Character::PlayVoiceSound(USoundCue* VoiceSound)
{
	if (!IsValid(VoiceSound))
	{
		return;
	}
	VoiceSoundComponent->SetSound(VoiceSound);
	VoiceSoundComponent->Play();
}

void AUndegard_Character::MoveForward(float value) {
	AddMovementInput(GetActorForwardVector()*value);
}
void AUndegard_Character::MoveRight(float value) {
	AddMovementInput(GetActorRightVector()*value);
}

void AUndegard_Character::Sprint()
{
	bIsSprinting = !bIsSprinting;
}

void AUndegard_Character::Jump()
{
	Super::Jump();
}

void AUndegard_Character::StopJumping()
{
	Super::StopJumping();
}

void AUndegard_Character::StartWeaponAction()
{
	if (!bCanCharacterUseWeapon)
	{
		return;
	}

	if (IsValid(CurrentWeapon) && bIsDoingMelee == false)
	{
		CurrentWeapon->StartAction();
	}
}

void AUndegard_Character::StopWeaponAction()
{
	if (!bCanCharacterUseWeapon)
	{
		return;
	}

	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopAction();
	}
}

void AUndegard_Character::SwitchWeaponMode()
{
	if (IsValid(CurrentWeapon))
	{
		AUndegard_Rifle* RifleWeaponReference = Cast<AUndegard_Rifle>(CurrentWeapon);
		if (IsValid(RifleWeaponReference))
		{
			BP_CharacterActionDebug();
			RifleWeaponReference->bIsAutomaticShootActivated = !RifleWeaponReference->bIsAutomaticShootActivated;
		}
	}
}

void AUndegard_Character::CreateInitialWeapon()
{
	if (IsValid(InitialWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<AUndegard_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());

		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void AUndegard_Character::AddControllerPitchInput(float value)
{
	Super::AddControllerPitchInput(bIsLookInverted?-value:value);
}

FVector AUndegard_Character::GetPawnViewLocation() const
{
	if (IsValid(FPSCameraComponent) && bUseFirstPersonView)
	{
		return FPSCameraComponent->GetComponentLocation();
	}

	if (IsValid(TPSCameraComponent) && !bUseFirstPersonView)
	{
		return TPSCameraComponent->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}


