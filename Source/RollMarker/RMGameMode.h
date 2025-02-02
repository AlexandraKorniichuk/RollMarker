// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RMGameMode.generated.h"

class ARMAIPawn;
/**
 * 
 */
UCLASS()
class ROLLMARKER_API ARMGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	int TargetsToSpawn = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(ClampMin=0, ClampMax=100))
	int CleanersPercentToSpawn = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	TSubclassOf<AActor> SpawnAIAreaClas;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	TSubclassOf<ARMAIPawn> BaseTargetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	TSubclassOf<ARMAIPawn> CleanersClass;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetTargetsToSpawn() const { return TargetsToSpawn; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCleanersToSpawn() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ARMAIPawn*> GetSpawnedTargets() const { return SpawnedTargets; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ARMAIPawn*> GetSpawnedCleaners() const { return SpawnedCleaners; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsEndGame(int TargetsAmount) const;

private:
	TArray<ARMAIPawn*> SpawnedTargets;
	TArray<ARMAIPawn*> SpawnedCleaners;
};
