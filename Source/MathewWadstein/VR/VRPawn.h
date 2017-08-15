// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerInterface.h"
#include "VRPawn.generated.h"

UCLASS()
class MATHEWWADSTEIN_API AVRPawn : public ACharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	AVRPawn();

	// -------- IPlayerInterface begins -----------------

	virtual void AddScore(int32 Value) override;

	virtual void ResetScore() override;

	// -------- IPlayerInterface ends -----------------

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	/** Sets the current player score to all InGamePlayerScoreInterface actors in the World  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void UpdateScoreOnAllPlayerScoreActors();

	/** Find all actors with InGamePlayerScoreInterface and store them into the array */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void FindAllInGamePlayerScoreActors();

	/** Spawns all needed FX when we hit something  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SpawnImpactFX(FHitResult& Hit);
	
	// -----------------------------------------------------------------------------------

	/** References to all Score Widgets in the World */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> InGamePlayerScoreActors;

	/** Score of this player  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 PlayerScore = 0;
	
	/* Gun Muzzle Scene Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* GunMuzzle;
	
	/** Right Controller  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* RightController;
	
	/* Right Mesh Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RightStaticMeshComponent;

	/* Emitter Template */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* EmitterTemplate;

	// -----------------------------------------------------------------------------------

	void Fire();
	
	void MoveForward(float Value);

	void MoveRight(float Value);

	void LookUp(float Value);

	void Turn(float Value);
	
};
