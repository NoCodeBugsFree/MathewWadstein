// Fill out your copyright notice in the Description page of Project Settings.

#include "InGamePlayerScore.h"
#include "Components/WidgetComponent.h"
#include "PlayerScoreWidget.h"

// Sets default values
AInGamePlayerScore::AInGamePlayerScore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(SceneComponent);
}

void AInGamePlayerScore::UpdateDisplayScore(int32 NewScoreValue)
{
	if (Widget)
	{
		UPlayerScoreWidget* PlayerScoreWidget = Cast<UPlayerScoreWidget>(Widget->GetUserWidgetObject());
		if (PlayerScoreWidget)
		{
			PlayerScoreWidget->UpdateScore(NewScoreValue);
		}
	}
}

// Called when the game starts or when spawned
void AInGamePlayerScore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInGamePlayerScore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

