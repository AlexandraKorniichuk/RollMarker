// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RMGameState.generated.h"

class ARMAIPawn;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTargetsBeenColored, ARMAIPawn*, Target, bool, bWasCleaner, bool, bWasCleaned);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCleanersAmountChanged, int, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameEnded);

UCLASS()
class ROLLMARKER_API ARMGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTargetColored(ARMAIPawn* Target, bool bWasCleaner, bool bWasCleaned);

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FTargetsBeenColored OnTargetsBeenColored;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FCleanersAmountChanged OnCleanersAmountChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FGameEnded OnGameEnded;

	UFUNCTION(BlueprintCallable)
	int GetCleanersAmount() const { return Cleaners.Num(); }

private:
	TArray<ARMAIPawn*> Targets;
	TArray<ARMAIPawn*> Cleaners;
};
