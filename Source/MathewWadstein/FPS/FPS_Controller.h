// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FPS_Controller.generated.h"

/**
*
*/
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UFPS_Controller : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IFPS_Controller
{
	GENERATED_IINTERFACE_BODY()

public:

	/** Adds some score to current player's score  */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void HadleUpdateScore(int32 Value);

	/** Returns  current player's score   */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	int32 GetScore();

	/** Sets up bIsSprinting value  */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void SetIsSprinting(bool NewIsSprinting);
};
