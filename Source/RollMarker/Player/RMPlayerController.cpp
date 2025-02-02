// Fill out your copyright notice in the Description page of Project Settings.


#include "RMPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "RollMarker/UI/RMGameWidget.h"

void ARMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());

	WidgetInstance = CreateWidget<URMGameWidget>(this, WidgetClass);
	if (WidgetInstance)
	{
		WidgetInstance->AddToViewport();
	}
}

void ARMPlayerController::SetupInputComponent()
{
	if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(MovementMappingContext, 0);
		}
	}
}
