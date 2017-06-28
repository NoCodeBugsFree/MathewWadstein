// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPS_Target.h"
#include "Target.generated.h"

UCLASS()
class MATHEWWADSTEIN_API ATarget : public AActor, public IFPS_Target
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ATarget();

	/** Calls to handle hit event on this actor   */
	virtual void HandleWasHit_Implementation(AActor* Hitter, int32 DamageValue) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Calls the game mode interface according function - 
	*   ask a game mode to Add one target to the target's list 
	*/
	void AddToRemainingTargetsInGameMode();

	/** Calls the game mode interface according function -
	*   ask a game mode to remove one target from the target's list
	*/
	void RemoveFromRemainingTargetsInGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/** Sets the color accordingly to health percentage  */
	void SetColor();

	/** Near to dead Color  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FLinearColor StartColor = FLinearColor::Red;

	/** Near to max health Color  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FLinearColor EndColor = FLinearColor::Green;

	/** Dynamic Material for this actor  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UMaterialInstanceDynamic* DynamicMaterial;

	/**  Starting Health Value of this actor, initialize in BeginPlay() */
	int32 StartingHealthValue;

	/** Amount of score which will be added to player's score when he will killed this guy  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 BonusValue = 200;

	/** Amount of score which will be added to player's score per hit  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 TargetScorePerHitValue = 34;

	/** Represents target health  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 HealthValue = 100;

	/* Represents Static mesh of the target  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;
	
};
