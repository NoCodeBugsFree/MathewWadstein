// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerScoreWidget.h"

void UPlayerScoreWidget::NativeConstruct()
{
	Super::NativePreConstruct();

	UpdateScore(0);
}
