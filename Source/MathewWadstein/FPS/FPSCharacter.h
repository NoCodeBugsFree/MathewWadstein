// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPS_Interface.h"
#include "FPSCharacter.generated.h"

UCLASS()
class MATHEWWADSTEIN_API AFPSCharacter : public ACharacter, public IFPS_Interface
{
	GENERATED_BODY()
	
	/** First person camera  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPS_Camera;
	
public:

	// Sets default values for this character's properties
	AFPSCharacter();

	// -----------------------------------------------------------------------------------
	//			IFPS_Interface override
	// -----------------------------------------------------------------------------------
	
	/** Calls when player wants to fire  */
	virtual void Fire_Implementation() override;

	/** Calls to toggle player's crouch */
	virtual void ToggleCrouch_Implementation(bool bIsCrouched) override;

	/** Calls to toggle player's sprint */
	virtual void ToggleSprint_Implementation(bool bIsSprinting) override;

	// -----------------------------------------------------------------------------------

	/** Generic function for spawning all impact effects  */
	void SpawnImpactFX(FHitResult& HitResult);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	
	/** Player's stamina  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 600.f;

	/** Player's stamina  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 1200.f;

	/** Player's current stamina  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float CurrentStamina = 10.f;

	/** Player's Max available stamina  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float MaxStamina = 10.f;

	/** Amount of stamina to drain per second when character is running  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float SprintStaminaDrain = 2.f;

	/** Amount of stamina when it will be possible to start sprinting again, after previous stamina depletion  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float RequiredStaminaForStartSprinting = 2.f;

	/** Amount of stamina to add per second when character is not running  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenRate = 1;

	/** General stamina timer. Uses for Increase/Decrease Stamina */
	FTimerHandle StaminaTimer;

	/* Emitter Template for impact FX */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* EmitterTemplate;

	/** Damage to apply to damageable objects per hit  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 DamageValue = 34;

	/** The distance to ray cast when we fire */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float FireDistance = 10000.f;

	/** Template for crosshair widget  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> CrosshairWidgetClass;
	
	/** Current crosshair widget reference   */
	UPROPERTY()
	class UUserWidget* CurrentCrosshairWidget;
	
	// -----------------------------------------------------------------------------------

	/** Create Crosshair  */
	void CreateCrosshairWidget();

	/** Attempt to increase stamina  */
	void IncreaseStamina();

	/**  Attempt to decrease stamina  */
	void DecreaseStamina();
	
public:	
	
	/** Returns FPS_Camera subobject **/
	FORCEINLINE class UCameraComponent* GetFPS_Camera() const { return FPS_Camera; }
	
};
