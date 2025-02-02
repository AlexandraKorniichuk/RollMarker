// Fill out your copyright notice in the Description page of Project Settings.


#include "RMPawn.h"

#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "RMAIPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RollMarker/RMSettings.h"

ARMPawn::ARMPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionProfileName(TEXT("Pawn"));
	Mesh->SetVisibility(true);
	
	Mesh->SetSimulatePhysics(true);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	DirectionArrow->SetupAttachment(RootComponent);
	DirectionArrow->ArrowLength = 300.0f;
	DirectionArrow->ArrowSize = 1.0f;
	DirectionArrow->ArrowColor = FColor::White;
	DirectionArrow->SetHiddenInGame(false);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bUsePawnControlRotation = true; 

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); 
	Camera->bUsePawnControlRotation = false;
}

void ARMPawn::BeginPlay()
{
	Super::BeginPlay();

	TargetMaterial = Mesh->CreateDynamicMaterialInstance(0, Mesh->GetMaterial(0));
	TargetMaterial->SetVectorParameterValue("Color", URMSettings::Get()->TargetColor);

	Mesh->OnComponentHit.AddDynamic(this, &ARMPawn::OnHit);
}

void ARMPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ARMPawn::MoveX);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ARMPawn::MoveY);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARMPawn::Look);
	}
}

void ARMPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector OutLocation;
	FRotator OutRotation;
	GetActorEyesViewPoint(OutLocation, OutRotation);

	const FVector CameraVector = OutRotation.Vector() * FVector(1.f, 1.f, 0.f);
	const FVector ForwardVector = CameraVector * GetPendingMovementInputVector().X;
	const FVector RightVector = FVector::CrossProduct(FVector::ZAxisVector, CameraVector) * GetPendingMovementInputVector().Y;

	const FVector Force = (ForwardVector + RightVector) * MovementForce;
	Mesh->AddForce(Force);
	
	ConsumeMovementInputVector();

	UpdateArrow(DeltaSeconds);
}

void ARMPawn::UpdateArrow(float DeltaSeconds)
{
	const float InterpSpeed = 10.0f;

	const FRotator Rotator = FMath::RInterpTo(DirectionArrow->GetComponentRotation(),
	                                          FRotator(0.0f, GetVelocity().Rotation().Yaw, 0.0f),
	                                          DeltaSeconds, InterpSpeed);
	DirectionArrow->SetWorldRotation(Rotator);

	const float ArrowLength = FMath::FInterpTo(CurrentVelocitySize,
	                                           GetVelocity().Size(), DeltaSeconds, InterpSpeed);
	DirectionArrow->SetArrowLength(ArrowLength / 10.0f);
	
	CurrentVelocitySize = GetVelocity().Size();
}

void ARMPawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	ARMAIPawn* HitPawn = Cast<ARMAIPawn>(OtherActor);

	if (!HitPawn)
	{
		return;
	}

	if (HitPawn->GetCurrentColor() == URMSettings::Get()->TargetColor)
	{
		return;
	}
	
	HitPawn->ColorMesh(URMSettings::Get()->TargetColor);
	
	SpawnEffects(Hit.Location);
}

void ARMPawn::MoveX(const FInputActionValue& Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value.Get<float>());
}

void ARMPawn::MoveY(const FInputActionValue& Value)
{
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value.Get<float>());
}

void ARMPawn::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ARMPawn::SpawnEffects(const FVector& Location) const
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitVFX, Location);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Location);
}
