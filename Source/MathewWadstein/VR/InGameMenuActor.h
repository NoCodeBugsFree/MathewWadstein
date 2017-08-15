// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MenuInterface.h"
#include "InGameMenuActor.generated.h"

UCLASS()
class MATHEWWADSTEIN_API AInGameMenuActor : public AActor, public IMenuInterface
{
	GENERATED_BODY()
	
public:	
	
	/** Menu Interface  */
	virtual void InteractWithMenu(UPrimitiveComponent* HitComp) override;
	
protected:

	// Sets default values for this actor's properties
	AInGameMenuActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartGame(float DelayToStart = 0.0f);

	void QuitGame(float DelayToStart = 0.0f);

	void PlayStartButtonFX();

	void PlayQuitButtonFX();

private:

	/** Time to show push button fx and after continue the game logic  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float ToggleButtonDelayTime = 1.5f;
	
	/* Box Collision Component for start button */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* StarButtonBoxComponent;

	/* Box Collision Component for start button */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* QuitButtonBoxComponent;
	
	/*  Scene Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

	/*  Widget Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Widget;
	
};
