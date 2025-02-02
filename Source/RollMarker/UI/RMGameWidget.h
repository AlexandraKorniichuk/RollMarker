// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RMGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROLLMARKER_API URMGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetCleanersAmount(int CleanersAmount);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowEndGame();
};
