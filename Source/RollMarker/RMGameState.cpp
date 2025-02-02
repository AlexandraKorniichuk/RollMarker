// Fill out your copyright notice in the Description page of Project Settings.


#include "RMGameState.h"

#include "RMGameMode.h"
#include "Kismet/GameplayStatics.h"

void ARMGameState::BeginPlay()
{
	Super::BeginPlay();
	
	const ARMGameMode* GameMode = Cast<ARMGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		return;
	}

	Targets = GameMode->GetSpawnedTargets();
	Cleaners = GameMode->GetSpawnedCleaners();

	UGameplayStatics::SetGamePaused(GetWorld(), false);

	OnTargetsBeenColored.AddDynamic(this, &ARMGameState::OnTargetColored);
}

void ARMGameState::OnTargetColored(ARMAIPawn* Target, bool bWasCleaner, bool bWasCleaned)
{
	if (bWasCleaned)
	{
		Targets.AddUnique(Target);
		return;
	}
	if (bWasCleaner)
	{
		Cleaners.Remove(Target);
		OnCleanersAmountChanged.Broadcast(Cleaners.Num());
	}
	else
	{
		Targets.Remove(Target);
	}

	const ARMGameMode* GameMode = Cast<ARMGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode->IsEndGame(Targets.Num() + Cleaners.Num()))
	{
		OnGameEnded.Broadcast();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}
