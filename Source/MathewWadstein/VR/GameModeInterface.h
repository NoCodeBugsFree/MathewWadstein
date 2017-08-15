// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MATHEWWADSTEIN_API IGameModeInterface
{
	GENERATED_BODY()

public:
	
	virtual void StartGame() = 0;

	virtual void QuitGame() = 0;
	
};
