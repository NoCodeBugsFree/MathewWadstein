// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "PlayerInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->InitialSpeed = 200.f;
	ProjectileMovementComponent->MaxSpeed = 5000.f;

	InitialLifeSpan = 10.f;
}

void AEnemy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->InitialSpeed = FMath::RandRange(MinSpeed, MaxSpeed);
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/** Interface BlueprintNativeEvent example  */
void AEnemy::Foo_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("Hello from cpp!"));
}

void AEnemy::WasHit(AActor* DamageCauser)
{ 
	if (DamageCauser)
	{
			if (DamageCauser->GetClass()->ImplementsInterface(UPlayerInterface::StaticClass()))
			{
				if (IPlayerInterface* Player = Cast<IPlayerInterface>(DamageCauser))
				{
					// Call interface function here
					Player->AddScore(ScoreToAdd);
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Target doesn't implement UPlayerInterface !"));
			}
	}
	SetLifeSpan(0.01f);
}

