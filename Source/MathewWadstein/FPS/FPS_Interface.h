// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPS_Interface.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UFPS_Interface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IFPS_Interface
{
	GENERATED_IINTERFACE_BODY()

public:

	/** Calls when player wants to fire  */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void Fire();

	/** Calls to toggle player's crouch */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void ToggleCrouch(bool bIsCrouched);

	/** Calls to toggle player's sprint */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void ToggleSprint(bool bIsSprinting);

};
