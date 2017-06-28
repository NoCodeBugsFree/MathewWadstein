// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPlayerController.h"
#include "GameFramework/Character.h"
#include "FPS_Interface.h"
#include "Blueprint/UserWidget.h"

AFPSPlayerController::AFPSPlayerController()
{
	
}

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateHUD();

	/** updates score to zero  */
	UpdateHUD();

	bIsCrouching = false;
	bIsSprinting = false;
}

void AFPSPlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	/** Setup the current pawn reference */
	SetupCurrentPawn(InPawn);
	
}

void AFPSPlayerController::SetupCurrentPawn(APawn* InPawn)
{
	if (InPawn)
	{
		CurrentPawn = InPawn;
	}
}

void AFPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	// Movement
	InputComponent->BindAxis("MoveForward", this, &AFPSPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSPlayerController::MoveRight);
	
	// Mouse
	InputComponent->BindAxis("LookUp", this, &AFPSPlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &AFPSPlayerController::Turn);

	// Jump
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSPlayerController::StopJumping);

	// Fire
	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSPlayerController::Fire);

	// Crouch
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AFPSPlayerController::ToggleCrouch);

	// Sprint
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AFPSPlayerController::ToggleSprint);
}

void AFPSPlayerController::AddScore(int32 Amount)
{
	PlayerScore += Amount;
	UpdateHUD();
}

void AFPSPlayerController::HadleUpdateScore_Implementation(int32 Value)
{
	AddScore(Value);
}

int32 AFPSPlayerController::GetScore_Implementation()
{
	return PlayerScore;
}

void AFPSPlayerController::SetIsSprinting_Implementation(bool NewIsSprinting)
{
	bIsSprinting = NewIsSprinting;
}

void AFPSPlayerController::CreateHUD()
{
	if (HUDWidgetClass)
	{
		CurrentHUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentHUDWidget)
		{
			CurrentHUDWidget->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentHUDWidget == NULL"));
	}
}


// ---- Input Binding --------------------------------------------------------------------

void AFPSPlayerController::Fire()
{
	if (CurrentPawn)
	{
 		IFPS_Interface* FPS_InterfaceObject = Cast<IFPS_Interface>(CurrentPawn);
 		if (FPS_InterfaceObject)
 		{
 			FPS_InterfaceObject->Execute_Fire(CurrentPawn);
 		}
	}
}

void AFPSPlayerController::MoveForward(float Value)
{
	if (CurrentPawn)
	{
		CurrentPawn->AddMovementInput(CurrentPawn->GetActorForwardVector(), Value);
	}
}

void AFPSPlayerController::MoveRight(float Value)
{
	if (CurrentPawn)
	{
		CurrentPawn->AddMovementInput(CurrentPawn->GetActorRightVector(), Value);
	}
}

void AFPSPlayerController::LookUp(float Value)
{
	AddPitchInput(Value);
}

void AFPSPlayerController::Turn(float Value)
{
	AddYawInput(Value);
}

void AFPSPlayerController::Jump()
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void AFPSPlayerController::StopJumping()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
	}
}

void AFPSPlayerController::ToggleCrouch()
{
	if (ACharacter* PotentialCharacter = GetCharacter())
	{
		/** if possessed character implement interface - toggle crouch state  */
		IFPS_Interface* IFPS_InterfaceObject = Cast<IFPS_Interface>(PotentialCharacter);
		if (IFPS_InterfaceObject)
		{
			IFPS_InterfaceObject->Execute_ToggleCrouch(PotentialCharacter, bIsCrouching);
		}
	}
	bIsCrouching = !bIsCrouching;
}

void AFPSPlayerController::ToggleSprint()
{
	bIsSprinting = !bIsSprinting;
	if (ACharacter* PotentialCharacter = GetCharacter())
	{
		/** if possessed character implement interface - toggle sprint state  */
		IFPS_Interface* IFPS_InterfaceObject = Cast<IFPS_Interface>(PotentialCharacter);
		if (IFPS_InterfaceObject)
		{
			IFPS_InterfaceObject->Execute_ToggleSprint(PotentialCharacter, bIsSprinting);
		}
	}
}
