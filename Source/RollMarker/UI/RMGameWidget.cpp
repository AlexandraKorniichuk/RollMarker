// Fill out your copyright notice in the Description page of Project Settings.


#include "RMGameWidget.h"

#include "RollMarker/RMGameState.h"

void URMGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ARMGameState* GameState = Cast<ARMGameState>(GetWorld()->GetGameState());
	if (!GameState)
	{
		return;
	}

	GameState->OnCleanersAmountChanged.AddDynamic(this, &URMGameWidget::SetCleanersAmount);
	GameState->OnGameEnded.AddDynamic(this, &URMGameWidget::ShowEndGame);
	SetCleanersAmount(GameState->GetCleanersAmount());
}
