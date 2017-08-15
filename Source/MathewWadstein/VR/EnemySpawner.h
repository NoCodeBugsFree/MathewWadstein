// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnerInterface.h"
#include "EnemySpawner.generated.h"

UCLASS()
class MATHEWWADSTEIN_API AEnemySpawner : public AActor, public IEnemySpawnerInterface
{
	GENERATED_BODY()

public:

	// --------- IEnemySpawnerInterface -------------------------------------

	virtual void HandleSpawnEnemy() override;

	// --------- IEnemySpawnerInterface -------------------------------------

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AEnemySpawner();

	/** Spawns Enemy  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SpawnEnemy();
	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEnemy> EnemyClass;

	/* Scene Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

	/* Billboard Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* Bill;
	
	/* Arrow Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* ArrowComponent;
	
};
