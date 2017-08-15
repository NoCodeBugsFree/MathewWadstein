// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "Enemy.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	Bill = CreateDefaultSubobject<UBillboardComponent>(TEXT("Bill"));
	Bill->SetupAttachment(RootComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}
	
// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy()
{
	if (EnemyClass)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			
			FTransform SpawnTransform = SceneComponent->GetComponentTransform();

			AEnemy* SpawnedEnemy = World->SpawnActor<AEnemy>(EnemyClass, SpawnTransform, SpawnParams);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyClass == NULL"));
	}
}

void AEnemySpawner::HandleSpawnEnemy()
{
	SpawnEnemy();
}