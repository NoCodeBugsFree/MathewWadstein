// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawnerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemySpawnerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MATHEWWADSTEIN_API IEnemySpawnerInterface
{
	GENERATED_BODY()

public:
	
	virtual void HandleSpawnEnemy() = 0;
	
};
