// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGamePlayerScoreInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInGamePlayerScoreInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MATHEWWADSTEIN_API IInGamePlayerScoreInterface
{
	GENERATED_BODY()

public:

	virtual void UpdateDisplayScore(int32 NewScoreValue) = 0;
	
	
};
