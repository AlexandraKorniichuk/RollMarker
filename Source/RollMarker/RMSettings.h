// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "RMSettings.generated.h"

UCLASS(Config=Game, DefaultConfig)
class ROLLMARKER_API URMSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName=GetRMSettings)
	static const URMSettings* Get()
	{
		return GetDefault<URMSettings>();
	}
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	FLinearColor TargetColor = FLinearColor::Yellow;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	FLinearColor BaseColor = FLinearColor::Black;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	FLinearColor CleanersColor = FLinearColor::White;
};
