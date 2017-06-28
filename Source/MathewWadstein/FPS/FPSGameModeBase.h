// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPS_GameMode.h"
#include "FPSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MATHEWWADSTEIN_API AFPSGameModeBase : public AGameModeBase, public IFPS_GameMode
{
	GENERATED_BODY()

public:

	/** Simple check to end the game  */
	void HandleGameOver();

	// --------IFPS_GameMode interface override -----------------------------------------------------

	/** After creating target in the world adds one to target's list  */
	virtual void RemoveTargetFromRemaining_Implementation() override;

	/** After destroying target remove it from target's list */
	virtual void AddTargetToRemaining_Implementation() override;

	// -----------------------------------------------------------------------------------

protected:

	/** Game Over Widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> GameOverWidgetClass;

private:
	
	/** The amount of targets to win the game  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 TargetRemaining = 0;
	
	
};
