// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MATHEWWADSTEIN_API IPlayerInterface
{
	GENERATED_BODY()
	
public:
	
	virtual void AddScore(int32 Value) = 0;

	virtual void ResetScore() = 0;
};
