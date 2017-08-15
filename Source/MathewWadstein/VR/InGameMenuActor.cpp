// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenuActor.h"
#include "Components/WidgetComponent.h"
#include "MenuWidget.h"
#include "Components/BoxComponent.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
AInGameMenuActor::AInGameMenuActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(SceneComponent);

	StarButtonBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("StarButtonBoxComponent"));
	StarButtonBoxComponent->SetupAttachment(RootComponent);
	StarButtonBoxComponent->SetCollisionProfileName("UI");

	QuitButtonBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("QuitButtonBoxComponent"));
	QuitButtonBoxComponent->SetupAttachment(RootComponent);
	QuitButtonBoxComponent->SetCollisionProfileName("UI");
}

// Called when the game starts or when spawned
void AInGameMenuActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInGameMenuActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInGameMenuActor::StartGame(float DelayToStart /*= 0.0f*/)
{
	/** starts right now  */
	if (DelayToStart == 0.0f)
	{
		if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(UGameModeInterface::StaticClass()))
		{
			if (IGameModeInterface* GameMode = Cast<IGameModeInterface>(GetWorld()->GetAuthGameMode()))
			{
				GameMode->StartGame();
			}
		}
	}
	else /** starts after delay */
	{
		FTimerDelegate StartDelegate;
		StartDelegate.BindLambda( [&] { 

			if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(UGameModeInterface::StaticClass()))
			{
				if (IGameModeInterface* GameMode = Cast<IGameModeInterface>(GetWorld()->GetAuthGameMode()))
				{
					GameMode->StartGame();
				}
			}
		});
		
		FTimerHandle StartTimer;
		GetWorldTimerManager().SetTimer(StartTimer, StartDelegate, DelayToStart, false);
	}
	
}

void AInGameMenuActor::QuitGame(float DelayToStart /*= 0.0f*/)
{
	/** Quit now  */
	if (DelayToStart == 0.f)
	{
		if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(UGameModeInterface::StaticClass()))
		{
			if (IGameModeInterface* GameMode = Cast<IGameModeInterface>(GetWorld()->GetAuthGameMode()))
			{
				GameMode->QuitGame();
				SetLifeSpan(0.01f);
			}
		}
	}
	else /** Quit after delay */
	{
		FTimerDelegate QuitDelegate;
		QuitDelegate.BindLambda( [&] {
			if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(UGameModeInterface::StaticClass()))
			{
				if (IGameModeInterface* GameMode = Cast<IGameModeInterface>(GetWorld()->GetAuthGameMode()))
				{
					GameMode->QuitGame();
					SetLifeSpan(0.01f);
				}
			}
		});
		
		FTimerHandle QuitTimer;
		GetWorldTimerManager().SetTimer(QuitTimer, QuitDelegate, ToggleButtonDelayTime, false);
	}
}

void AInGameMenuActor::InteractWithMenu(UPrimitiveComponent* HitComp)
{
	if (HitComp)
	{
		/** Start button pressed  */
		if (HitComp->ComponentHasTag("StartBox"))
		{
			/** Push Button FX for Start Button  */
			PlayStartButtonFX();

			/** Start the Game  */
			StartGame(ToggleButtonDelayTime);
		}
		/** Quit button pressed */
		else if (HitComp->ComponentHasTag("QuitBox"))
		{
			/** Push Button FX for Quit Button  */
			PlayQuitButtonFX();

			/** Quit the Game  */
			QuitGame(ToggleButtonDelayTime);
		}
	}
}

void AInGameMenuActor::PlayStartButtonFX()
{
	if (Widget)
	{
		UMenuWidget* MenuWidget = Cast<UMenuWidget>(Widget->GetUserWidgetObject());
		if (MenuWidget)
		{
			MenuWidget->ToggleStartButton();
		}
	}
}

void AInGameMenuActor::PlayQuitButtonFX()
{
	if (Widget)
	{
		UMenuWidget* MenuWidget = Cast<UMenuWidget>(Widget->GetUserWidgetObject());
		if (MenuWidget)
		{
			MenuWidget->ToggleQuitButton();
		}
	}
}
