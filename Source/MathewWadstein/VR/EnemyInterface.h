// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MATHEWWADSTEIN_API IEnemyInterface
{
	GENERATED_BODY()

	
public:

	/** BlueprintNativeEvent test  */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void Foo();
	virtual void Foo_Implementation() = 0;
	
	virtual void WasHit(AActor* DamageCauser) = 0;
};

