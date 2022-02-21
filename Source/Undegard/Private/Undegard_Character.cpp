// Fill out your copyright notice in the Description page of Project Settings.


#include "Undegard_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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
}

// Called when the game starts or when spawned
void AUndegard_Character::BeginPlay()
{
	Super::BeginPlay();
	
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

void AUndegard_Character::AddControllerPitchInput(float value)
{
	Super::AddControllerPitchInput(bIsLookInverted?-value:value);
}


