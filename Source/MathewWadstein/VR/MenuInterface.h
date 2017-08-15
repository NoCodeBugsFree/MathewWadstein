// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MATHEWWADSTEIN_API IMenuInterface
{
	GENERATED_BODY()
	
public:
	
	virtual void InteractWithMenu(UPrimitiveComponent* HitComp) = 0;
	
};
