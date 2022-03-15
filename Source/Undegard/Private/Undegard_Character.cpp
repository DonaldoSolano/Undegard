// Fill out your copyright notice in the Description page of Project Settings.

#include "Undegard/Undegard.h"
#include "Undegard_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Undegard_Weapon.h"
#include "Undegard_Rifle.h"

// Sets default values
AUndegard_Character::AUndegard_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseFirstPersonView = true;

	bIsSprinting = false;

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
}

// Called when the game starts or when spawned
void AUndegard_Character::BeginPlay()
{
	Super::BeginPlay();
	CreateInitialWeapon();
	InitializeReferences();
}

void AUndegard_Character::InitializeReferences()
{
	if (IsValid(GetMesh()))
	{
		AnimInstance = GetMesh()->GetAnimInstance();
	}
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
}

void AUndegard_Character::StartMelee()
{
	if (IsValid(AnimInstance) && IsValid(MeleeMontage))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player starts melee action"));
		AnimInstance->Montage_Play(MeleeMontage);
	}

}

void AUndegard_Character::StopMelee() 
{
	UE_LOG(LogTemp, Warning, TEXT("Player stops melee action"));
}

void AUndegard_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

bool AUndegard_Character::HasKey(FName KeyTag)
{
	return DoorKeys.Contains(KeyTag);
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
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartAction();
	}
}

void AUndegard_Character::StopWeaponAction()
{
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


