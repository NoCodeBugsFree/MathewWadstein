// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InGamePlayerScoreInterface.h"
#include "InGamePlayerScore.generated.h"

UCLASS()
class MATHEWWADSTEIN_API AInGamePlayerScore : public AActor, public IInGamePlayerScoreInterface
{
	GENERATED_BODY()
	
public:	

	void UpdateDisplayScore(int32 NewScoreValue) override;
	
protected:

	// Sets default values for this actor's properties
	AInGamePlayerScore();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	/*  Scene Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;
	
	/*  Widget Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Widget;
	
	
	
};
