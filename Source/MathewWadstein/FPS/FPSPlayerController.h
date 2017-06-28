// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPS_Controller.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MATHEWWADSTEIN_API AFPSPlayerController : public APlayerController, public IFPS_Controller
{
	GENERATED_BODY()

public:

	AFPSPlayerController();

	virtual void BeginPlay() override;

	virtual void Possess(APawn* InPawn) override;

	/** Setup the current pawn reference */
	void SetupCurrentPawn(APawn* InPawn);
	
	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;

	/** Returns current player's score  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	int32 GetPlayerScore() const { return PlayerScore; }

	/** Adds/subtracts some score to/from current player's score
	* @param Amount can be "+" or "-"	
	*/
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void AddScore(int32 Amount);

	/** Calls when needed to update HUD (score) to current PlayerScore   */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void UpdateHUD();

	// ----- IFPS_Controller interface override ------------------------------------------------------------------

	/** Adds some score to current player's score  */
	virtual void HadleUpdateScore_Implementation(int32 Value);

	/** Returns  current player's score   */
	virtual int32 GetScore_Implementation();

	/** Sets up bIsSprinting value  */
	virtual	void SetIsSprinting_Implementation(bool NewIsSprinting);

	// -----------------------------------------------------------------------------------

protected:

	/** HUD template Widget  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;
	
private:

	/** Shows whether or not character is in crouch state now  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsCrouching : 1;

	/** Shows whether or not character is in sprint state now */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsSprinting : 1;

	/** Current player's score  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 PlayerScore = 0;

	/** Current HUD Widget reference */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UUserWidget* CurrentHUDWidget;
	
	/** Reference for possessed pawn  */
	UPROPERTY()
	class APawn* CurrentPawn;
	
	/** HUD that shows the current score  */
	void CreateHUD();

	// -------- Basic Input Binding -------------------------------------------------------------------
	
	void Fire();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void LookUp(float Value);

	void Turn(float Value);

	void Jump();

	void StopJumping();

	void ToggleCrouch();

	void ToggleSprint();
	
};
