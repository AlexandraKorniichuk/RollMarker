// Fill out your copyright notice in the Description page of Project Settings.


#include "RMGameMode.h"

#include "RMAIPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ARMGameMode::BeginPlay()
{
	Super::BeginPlay();

	AActor* SpawnAIArea = UGameplayStatics::GetActorOfClass(GetWorld(), SpawnAIAreaClas);

	if (!SpawnAIArea)
	{
		return;
	}

	
	UStaticMeshComponent* Area = Cast<UStaticMeshComponent>(SpawnAIArea->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	FBoxSphereBounds Bounds = Area->Bounds;
	int CleanersAmount = GetCleanersToSpawn();
	int TargetsAmount = TargetsToSpawn - CleanersAmount;
	for (int i = 0; i < CleanersAmount; ++i)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ARMAIPawn* SpawnedActor = GetWorld()->SpawnActor<ARMAIPawn>(CleanersClass,
		                                                    UKismetMathLibrary::RandomPointInBoundingBox(Bounds.Origin, Bounds.BoxExtent),
		                                                    FRotator::ZeroRotator, SpawnParameters);
		if (SpawnedActor)
		{
			SpawnedCleaners.Add(SpawnedActor);
		}
	}

	for (int i = 0; i < TargetsAmount; ++i)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ARMAIPawn* SpawnedActor = GetWorld()->SpawnActor<ARMAIPawn>(BaseTargetClass,
		                                                    UKismetMathLibrary::RandomPointInBoundingBox(Bounds.Origin, Bounds.BoxExtent),
		                                                    FRotator::ZeroRotator, SpawnParameters);
		if (SpawnedActor)
		{
			SpawnedTargets.Add(SpawnedActor);
		}
	}
}

int ARMGameMode::GetCleanersToSpawn() const
{
	return TargetsToSpawn * CleanersPercentToSpawn / 100.0f;
}

bool ARMGameMode::IsEndGame(int TargetsAmount) const
{
	return TargetsAmount <= 0;
}
