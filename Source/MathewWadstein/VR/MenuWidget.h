// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATHEWWADSTEIN_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void ToggleStartButton();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void ToggleQuitButton();

};
