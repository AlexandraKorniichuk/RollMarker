// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RMPlayerController.generated.h"

class URMGameWidget;
class UInputMappingContext;

UCLASS()
class ROLLMARKER_API ARMPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* MovementMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<URMGameWidget> WidgetClass;
    
	UPROPERTY()
	URMGameWidget* WidgetInstance;
};
