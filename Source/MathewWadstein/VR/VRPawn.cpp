// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "DrawDebugHelpers.h"
#include "EnemyInterface.h"
#include "InGamePlayerScoreInterface.h"
#include "Kismet/GameplayStatics.h"
#include "MenuInterface.h"

// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->Hand = EControllerHand::Right;
	
	RightStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightStaticMeshComponent"));

	// Suppose to be attached to RightController
	// RightStaticMeshComponent->SetupAttachment(RightController);

	// but 
	RightStaticMeshComponent->SetupAttachment(RootComponent);
	RightStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightStaticMeshComponent->SetCollisionProfileName("NoCollision");

	GunMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("GunEndPoint"));
	GunMuzzle->SetupAttachment(RightStaticMeshComponent);

	bUseControllerRotationPitch = true;
	
}

void AVRPawn::AddScore(int32 Value)
{
	PlayerScore += Value;

	UpdateScoreOnAllPlayerScoreActors();
}

void AVRPawn::ResetScore()
{
	PlayerScore = 0;
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	/** Find all actors with InGamePlayerScoreInterface and store them into the array */
	FindAllInGamePlayerScoreActors();
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAxis("MoveForward", this, &AVRPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AVRPawn::MoveRight);

	InputComponent->BindAxis("LookUp", this, &AVRPawn::LookUp);
	InputComponent->BindAxis("Turn", this, &AVRPawn::Turn);
	
	InputComponent->BindAction("Fire", IE_Pressed, this, &AVRPawn::Fire);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void AVRPawn::UpdateScoreOnAllPlayerScoreActors()
{
	if (InGamePlayerScoreActors.Num() > 0)
	{
		for (AActor* PlayerScoreActor : InGamePlayerScoreActors)
		{
			/** Interface call  */
			if (PlayerScoreActor && PlayerScoreActor->GetClass()->ImplementsInterface(UInGamePlayerScoreInterface::StaticClass()))
			{
				IInGamePlayerScoreInterface* PlayerScoreInterfaceActor = Cast<IInGamePlayerScoreInterface>(PlayerScoreActor);
				if (PlayerScoreInterfaceActor)
				{
					PlayerScoreInterfaceActor->UpdateDisplayScore(PlayerScore);
				}
			}
		}
	}
}

void AVRPawn::FindAllInGamePlayerScoreActors()
{	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInGamePlayerScoreInterface::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		InGamePlayerScoreActors.AddUnique(Actor);
	}
}

void AVRPawn::SpawnImpactFX(FHitResult& Hit)
{
	if (EmitterTemplate)
	{
		FVector SpawnLocation = Hit.ImpactPoint;
		FRotator SpawnRotation = Hit.ImpactNormal.Rotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterTemplate, SpawnLocation, SpawnRotation);
	}
}

void AVRPawn::Fire()
{
	float Distance = 10000.f;
	
	FVector Direction = GunMuzzle->GetComponentRotation().Vector();
	FVector Start = GunMuzzle->GetComponentLocation();
	FVector End = Start + (Direction * Distance);
	
	FHitResult OutHit;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	
	bool bHasHitSomething = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionQueryParams);
	if (AActor* Target = OutHit.GetActor())
	{
		SpawnImpactFX(OutHit);

		/** Checking for Enemy Interface  */
		if (Target->GetClass()->ImplementsInterface(UEnemyInterface::StaticClass()))
		{
			if (IEnemyInterface* Enemy = Cast<IEnemyInterface>(Target))
			{
				Enemy->WasHit(this);
			}
		}

		/** Checking for UI Interface  */
		if (Target->GetClass()->ImplementsInterface(UMenuInterface::StaticClass()))
		{
			if (IMenuInterface* Menu = Cast<IMenuInterface>(Target))
			{
				Menu->InteractWithMenu(OutHit.GetComponent());
			}
		}

	}
	DrawDebugLine(GetWorld(), Start, End, FColor::MakeRandomColor(), true, 1.f, (uint8)0, 1.f);
}

void AVRPawn::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AVRPawn::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AVRPawn::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AVRPawn::Turn(float Value)
{
	AddControllerYawInput(Value);
}

