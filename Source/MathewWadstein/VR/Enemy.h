// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyInterface.h"
#include "Enemy.generated.h"

UCLASS()
class MATHEWWADSTEIN_API AEnemy : public AActor, public IEnemyInterface
{
	GENERATED_BODY()

public:

	// --------- Enemy Interface begins --------------------------

	/** BlueprintNativeEvent example  */
	virtual void Foo_Implementation() override;

	virtual void WasHit(AActor* DamageCauser) override;

	// --------- Enemy Interface ends --------------------------
	
protected:

	// Sets default values for this actor's properties
	AEnemy();

	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/** Minimum Enemy Speed  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float MinSpeed = 100.f;

	/** Maximum Enemy Speed  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 350.f;
	
	/*  Projectile Movement Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
	/** Reward to player  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 ScoreToAdd = 10;

	/* Scene Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;
	
	/* Static MeshComponent  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;
	
};
