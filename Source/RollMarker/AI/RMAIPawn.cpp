// Fill out your copyright notice in the Description page of Project Settings.


#include "RMAIPawn.h"

#include "RollMarker/RMGameState.h"
#include "RollMarker/RMSettings.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

ARMAIPawn::ARMAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionProfileName(TEXT("Pawn"));
	Mesh->SetVisibility(true);
	
	Mesh->SetSimulatePhysics(true);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ARMAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &ARMAIPawn::OnHit);
}

void ARMAIPawn::SetDynamicMaterial(FLinearColor Color)
{
	DynamicMaterial = Mesh->CreateDynamicMaterialInstance(0, Mesh->GetMaterial(0));
	ColorMesh(Color);
}

void ARMAIPawn::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ARMAIPawn* HitPawn = Cast<ARMAIPawn>(OtherActor);

	if (!HitPawn)
	{
		return;
	}
	
	TryColorToTargetColor(HitPawn, URMSettings::Get()->TargetColor, URMSettings::Get()->TargetColor);
}

void ARMAIPawn::ColorMesh_Implementation(FLinearColor Color)
{
	ARMGameState* GameState = Cast<ARMGameState>(GetWorld()->GetGameState());

	if (GameState)
	{
		const bool bWasCleaner = CurrentColor == URMSettings::Get()->CleanersColor;
		const bool bWasTarget = Color == URMSettings::Get()->BaseColor;
		GameState->OnTargetsBeenColored.Broadcast(this, bWasCleaner, bWasTarget);
	}

	DynamicMaterial->SetVectorParameterValue("Color", Color);
	CurrentColor = Color;
}

bool ARMAIPawn::TryColorToTargetColor(ARMAIPawn* OtherPawn, FLinearColor RequiredColor, FLinearColor TargetColor)
{
	if (OtherPawn && CurrentColor == RequiredColor && OtherPawn->GetCurrentColor() != URMSettings::Get()->CleanersColor)
	{
		OtherPawn->ColorMesh(TargetColor);
		return true;
	}

	return false;
}

