// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeInterface.h"
#include "VRGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MATHEWWADSTEIN_API AVRGameMode : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()
	
public:

	// -------  IGameModeInterface  ---------------------------------------------------------

	virtual void StartGame() override;

	virtual void QuitGame() override;

	// -------  IGameModeInterface  ------------------------------------------------------



	virtual void BeginPlay() override;

protected:

	/** Spawn Enemy Wave  */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void SpawnEnemyWave();
	virtual void SpawnEnemyWave_Implementation();

	UFUNCTION(Exec, Category = ExecFunctions)
	void HandleGameOver();

	void SetMenuActorsEnable(bool bNewEnable);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void HandleSpawningNewWave();

private:
	
	/**  Finds All Enemy Spawners in the world and spawns them into the array */
	void FindAllEnemySpawners();

	/**  Finds All Menu in the world and spawns them into the array */
	void FindAllMenu();

	/** Enemy Spawners  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<class AEnemySpawner*> EnemySpawners;

	/** Menu actors */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<class AInGameMenuActor*> InGameMenuActors;
	
	/** Enemies Per Wave  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<int32> EnemiesPerWave = { 3, 4, 5 };

	/** Delay PerWave  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float DelayPerWave = 3.f;

	/** Current Wave Number  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 CurrentWaveNumber = 0;
};
