// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPS_Target.generated.h"

/**
*
*/
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UFPS_Target: public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IFPS_Target
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/** Calls to handle hit event on this actor   */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void HandleWasHit(AActor* Hitter, int32 DamageValue);
};