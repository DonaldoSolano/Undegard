// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Undegard_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AUndegard_Weapon;
class AUndegard_Rifle;
class UAnimMontage;
class UAnimInstance;
class UCapsuleComponent;
class UUndegard_HealthComponent;
class AUndegard_GameMode;
class UUndegard_GameInstance;

UENUM(Blueprintable)
enum class EUndegard_CharacterType : uint8
{
	CharacterType_Player UMETA(DisplayName = "Player"),
	CharacterType_Enemy UMETA(DisplayName = "Enemy")
};

UCLASS()
class UNDEGARD_API AUndegard_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUndegard_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitializeReferences();

	void MoveForward(float value);
	void MoveRight(float value);
	void Sprint();
	virtual void Jump() override;
	virtual void StopJumping() override;

	

	void SwitchWeaponMode();

	void CreateInitialWeapon();

	virtual void AddControllerPitchInput(float value) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	bool bIsSprinting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
	bool bIsLookInverted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
	bool bUseFirstPersonView;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsDoingMelee;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	bool bCanCharacterUseWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	bool bCanMakeCombos;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsComboEnabled;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Game Over")
	bool bHasToDestroy;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
	bool bCanUseUltimate;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
	bool bIsUsingUltimate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate", meta =(ClampMin = 0.0, UIMin = 0.0))
	float MaxUltimateXP;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
	float CurrentUltimateXP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Time", meta = (ClampMin = 0.0, UIMin = 0.0))
	float MaxUltimateDuration;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate|Time")
	float CurrentUltimateDuration;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeDamage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (EditCondition = bCanMakeCombos, ClampMin = 1.0, UIMin = 1.0))
	float MaxComboMultiplier;

	UPROPERTY(BlueprintReadOnly, Category = "Melee" , meta = (EditCondition = bCanMakeCombos, ClampMin = 1.0, UIMin = 1.0))
	float CurrentComboMultiplier;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
	FName FPSCameraSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
	FName TPSCameraSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName MeleeSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Levels")
	FName MainMenuMapName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* TPSCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	TArray<FName> DoorKeys;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EUndegard_CharacterType CharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AUndegard_Weapon> InitialWeaponClass;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	AUndegard_Weapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> MeleeMontage;

	UAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* MeleeDetectorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UUndegard_HealthComponent* HealthComponent;

	AUndegard_GameMode* GameModeReference;

	UUndegard_GameInstance* GameInstanceReference;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

	void AddKey(FName NewKey);

	void AddHealth(float HealthToAdd);

	bool HasKey(FName KeyTag);

	void SetActionsState(bool NewState);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Visual Character Debug|Debug")
	void BP_CharacterActionDebug();

	void SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState);

	UFUNCTION()
	void MakeMeleeDamage(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnHealthChange(UUndegard_HealthComponent* CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);

	UFUNCTION(BlueprintCallable)
	void StartWeaponAction();

	UFUNCTION(BlueprintCallable)
	void StopWeaponAction();

	UFUNCTION(BlueprintCallable)
	void StartMelee();

	UFUNCTION(BlueprintCallable)
	void StopMelee();
	
	UFUNCTION(BlueprintCallable)
	void SetComboEnabled(bool NewState);

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION(BlueprintCallable)
	bool HasToDestroy() { return bHasToDestroy; };

	UFUNCTION(BlueprintCallable)
	void GainUltimateXP(float XPGained);

	UFUNCTION(BlueprintCallable)
	void StartUltimate();

	UFUNCTION(BlueprintCallable)
	void StopUltimate();

	UFUNCTION(BlueprintCallable)
	void GoToMainMenu();

	UFUNCTION(BlueprintCallable)
	EUndegard_CharacterType GetCharacterType() { return CharacterType; };

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GainUltimateXP(float XPGained);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_StartUltimate();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_StopUltimate();

};
