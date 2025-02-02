// Fill out your copyright notice in the Description page of Project Settings.


#include "RMAIController.h"

#include "RMAIPawn.h"

void ARMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ARMAIPawn* AIPawn = Cast<ARMAIPawn>(InPawn);
	if (AIPawn)
	{
		RunBehaviorTree(AIPawn->BehaviorTree);
	}
}
