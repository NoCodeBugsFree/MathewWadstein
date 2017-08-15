// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGameMode.h"
#include "EnemySpawner.h"
#include "EnemySpawnerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"
#include "InGameMenuActor.h"

void AVRGameMode::BeginPlay()
{
	Super::BeginPlay();

	FindAllEnemySpawners();

	FindAllMenu();
}

void AVRGameMode::SpawnEnemyWave_Implementation()
{
	if ( ! (CurrentWaveNumber > EnemiesPerWave.Num() - 1) )
	{	
		// Shuffling EnemySpawners in BP
		
		if (EnemySpawners.Num() > 0 && EnemiesPerWave.Num() > 0)
		{
			for (int32 i = 0; i < EnemiesPerWave[CurrentWaveNumber]; i++)
			{
				if (EnemySpawners.IsValidIndex(i) && EnemySpawners[i] && EnemySpawners[i]->GetClass()->ImplementsInterface(UEnemySpawnerInterface::StaticClass()))
				{
					if (IEnemySpawnerInterface* EnemySpawnerInterface = Cast<IEnemySpawnerInterface>(EnemySpawners[i]))
					{
						EnemySpawnerInterface->HandleSpawnEnemy();
					}
				}
			}
			CurrentWaveNumber++;
			FTimerHandle Timer;
			GetWorldTimerManager().SetTimer(Timer, this, &AVRGameMode::HandleSpawningNewWave, DelayPerWave, false);
		}
	}
	else
	{
		FTimerDelegate RestartLevelDelegate;
		RestartLevelDelegate.BindLambda( [&] {
			GetWorld()->GetFirstPlayerController()->ConsoleCommand("RestartLevel");
		});
		
		FTimerHandle RestartTimer;
		GetWorldTimerManager().SetTimer(RestartTimer, RestartLevelDelegate, 10.f, false);
	}
}

void AVRGameMode::HandleGameOver()
{
	SetMenuActorsEnable(true);
}

void AVRGameMode::SetMenuActorsEnable(bool bNewEnable)
{
	for (auto& InGameMenuActor : InGameMenuActors)
	{
		InGameMenuActor->SetActorHiddenInGame(!bNewEnable);
		InGameMenuActor->SetActorEnableCollision(bNewEnable);
	}
}

void AVRGameMode::FindAllEnemySpawners()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundActors);
	
	for (auto Actor : FoundActors)
	{
		AEnemySpawner* TestActor = Cast<AEnemySpawner>(Actor);
		if (TestActor)
		{
			EnemySpawners.AddUnique(TestActor);
		}
	}
}

void AVRGameMode::FindAllMenu()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInGameMenuActor::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		AInGameMenuActor* TestActor = Cast<AInGameMenuActor>(Actor);
		if (TestActor)
		{
			InGameMenuActors.AddUnique(TestActor);
		}
	}
}

void AVRGameMode::StartGame()
{
	SetMenuActorsEnable(false);
	HandleSpawningNewWave();
}

void AVRGameMode::QuitGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
