// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATHEWWADSTEIN_API UPlayerScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void UpdateScore(int32 NewScoreValue);
	
};
