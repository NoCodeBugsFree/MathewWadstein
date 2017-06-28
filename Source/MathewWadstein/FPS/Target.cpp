// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"
#include "FPS_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "FPS_GameMode.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	/** Store the initial heath in special variable  */
	StartingHealthValue = HealthValue;

	/** Create the Dynamic Material Instance  */
	if (StaticMeshComponent)
	{
		DynamicMaterial = StaticMeshComponent->CreateDynamicMaterialInstance(0);
	}

	/** set the initial color  */
	SetColor();

	/** add this guy to remaining targets in game mode  */
	AddToRemainingTargetsInGameMode();
}

void ATarget::AddToRemainingTargetsInGameMode()
{
	AGameModeBase* GameModeBase = Cast<AGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameModeBase)
	{
		IFPS_GameMode* FPS_GameModeObject = Cast<IFPS_GameMode>(GameModeBase);
		if (FPS_GameModeObject)
		{
			FPS_GameModeObject->Execute_AddTargetToRemaining(GameModeBase);
		}
	}
}

void ATarget::RemoveFromRemainingTargetsInGameMode()
{
	AGameModeBase* GameModeBase = Cast<AGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameModeBase)
	{
		IFPS_GameMode* FPS_GameModeObject = Cast<IFPS_GameMode>(GameModeBase);
		if (FPS_GameModeObject)
		{
			FPS_GameModeObject->Execute_RemoveTargetFromRemaining(GameModeBase);
		}
	}
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget::SetColor()
{
	if (DynamicMaterial)
	{
		float Alpha = FMath::Clamp((float)HealthValue / (float)StartingHealthValue, 0.f, 1.f);
		FLinearColor ColorToSet = UKismetMathLibrary::LinearColorLerp(StartColor, EndColor, Alpha);
		DynamicMaterial->SetVectorParameterValue("Color", ColorToSet);
	}
}

void ATarget::HandleWasHit_Implementation(AActor* Hitter, int32 DamageValue)
{
	if (Hitter)
	{
		IFPS_Controller* FPS_Controller = Cast<IFPS_Controller>(Hitter);
		if (FPS_Controller)
		{
			FPS_Controller->Execute_HadleUpdateScore(Hitter, TargetScorePerHitValue);
			HealthValue -= DamageValue;

			SetColor();

			/** Adds some bonus score and kill this actor */
			if (HealthValue <= 0)
			{
				FPS_Controller->Execute_HadleUpdateScore(Hitter, BonusValue);

				/** Remove from remaining targets */
				RemoveFromRemainingTargetsInGameMode();

				Destroy();
			}
		}
	}
}