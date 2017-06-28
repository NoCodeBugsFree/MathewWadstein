// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FPS_GameMode.generated.h"

/**
*
*/
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UFPS_GameMode : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IFPS_GameMode
{
	GENERATED_IINTERFACE_BODY()

public:

	/** After creating target in the world adds one to target's list  */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void RemoveTargetFromRemaining();

	/** After destroying target remove it from target's list */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void AddTargetToRemaining();
};
