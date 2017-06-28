// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AFPSGameModeBase::HandleGameOver()
{
	if (GameOverWidgetClass)
	{
		UUserWidget* CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
			PlayerController->bShowMouseCursor = true;
			PlayerController->DisableInput(PlayerController);
		}
	}
}

void AFPSGameModeBase::RemoveTargetFromRemaining_Implementation()
{
	TargetRemaining--;
	if (TargetRemaining <= 0)
	{
		HandleGameOver();
	}
}

void AFPSGameModeBase::AddTargetToRemaining_Implementation()
{
	TargetRemaining++;
}
