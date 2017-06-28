// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "FPS_Target.h"
#include "FPS_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	/** Camera rotates accordingly the controller rotation  */
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	/** First person camera  */
	FPS_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_Camera"));
	FPS_Camera->SetupAttachment(GetCapsuleComponent());
	FPS_Camera->RelativeLocation = FVector(0.f, 0.f, 50.f);
	FPS_Camera->bUsePawnControlRotation = true;
	
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 100.f;
	GetCharacterMovement()->CrouchedHalfHeight = 30.f;
	GetCharacterMovement()->MaxAcceleration = 1024.f;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CreateCrosshairWidget();

}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFPSCharacter::Fire_Implementation()
{
	FVector Direction = GetActorForwardVector();
	FVector Start = GetFPS_Camera()->GetComponentLocation();
	FVector End = Start + (Direction * FireDistance);

	FHitResult OutHit;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Camera, CollisionQueryParams);
	if (OutHit.GetActor())
	{
		/** Impact FX  */
		SpawnImpactFX(OutHit);

		/** Interface call */
		IFPS_Target* FPS_TargetObject = Cast<IFPS_Target>(OutHit.GetActor());
		if (FPS_TargetObject)
		{
			if (GetController())
			{
				FPS_TargetObject->Execute_HandleWasHit(OutHit.GetActor(), GetController(), DamageValue);
			}
		}
	}

	// DrawDebugLine(GetWorld(), Start, End, FColor::MakeRandomColor(), true, 10.f, (uint8)0, 10.f);
}

void AFPSCharacter::ToggleCrouch_Implementation(bool bIsCrouched)
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void AFPSCharacter::ToggleSprint_Implementation(bool bIsSprinting)
{
	if (bIsSprinting)
	{
		if (CurrentStamina > RequiredStaminaForStartSprinting)
		{
			GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
			GetWorldTimerManager().ClearTimer(StaminaTimer);
			GetWorldTimerManager().SetTimer(StaminaTimer, this, &AFPSCharacter::DecreaseStamina, 1.f, false);
		}
	} 
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		GetWorldTimerManager().ClearTimer(StaminaTimer);
		GetWorldTimerManager().SetTimer(StaminaTimer, this, &AFPSCharacter::IncreaseStamina, 1.f, false);
	}
}

void AFPSCharacter::IncreaseStamina()
{
	CurrentStamina += StaminaRegenRate;

	/** if we have more stamina then maximum - we are walking  */
	if (CurrentStamina >= MaxStamina)
	{
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.f, MaxStamina);
		GetWorldTimerManager().ClearTimer(StaminaTimer);
	}
	else 
	{
		GetWorldTimerManager().ClearTimer(StaminaTimer);
		GetWorldTimerManager().SetTimer(StaminaTimer, this, &AFPSCharacter::IncreaseStamina, 1.f, false);
	}
}

void AFPSCharacter::DecreaseStamina()
{
	/** Decrease Stamina only if we moving */
	if (GetCharacterMovement()->Velocity.Size() > 0)
	{
		CurrentStamina -= SprintStaminaDrain;
	}
	else /** Increase stamina if we not moving */
	{
		CurrentStamina += StaminaRegenRate;
	}
	
	/** if we have no more stamina - we are walking and we increase stamina again */
	if (CurrentStamina <= 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		GetWorldTimerManager().ClearTimer(StaminaTimer);
		GetWorldTimerManager().SetTimer(StaminaTimer, this, &AFPSCharacter::IncreaseStamina, 1.f, false);

		/** tells the controller that we force character to walking  */
		if (AController* Controller = GetController())
		{
			IFPS_Controller* FPS_ControllerObject = Cast<IFPS_Controller>(Controller);
			if (FPS_ControllerObject)
			{
				FPS_ControllerObject->Execute_SetIsSprinting(Controller, false);
			}
		}
	}
	else /** Decrease Stamina once more */
	{
		GetWorldTimerManager().ClearTimer(StaminaTimer);
		GetWorldTimerManager().SetTimer(StaminaTimer, this, &AFPSCharacter::DecreaseStamina, 1.f, false);
	}
	
}

void AFPSCharacter::SpawnImpactFX(FHitResult& HitResult)
{
	if (EmitterTemplate)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterTemplate, HitResult.Location);
	}
}


void AFPSCharacter::CreateCrosshairWidget()
{
	if (CrosshairWidgetClass)
	{
		CurrentCrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
		if (CurrentCrosshairWidget)
		{
			CurrentCrosshairWidget->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HUDWidgetClass == NULL"));
	}
}






