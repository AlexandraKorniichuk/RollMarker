// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RMPawn.generated.h"

class UNiagaraSystem;
class UArrowComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class ROLLMARKER_API ARMPawn : public APawn
{
	GENERATED_BODY()

public:
	ARMPawn();

protected:
	virtual void BeginPlay() override;

	void MoveX(const FInputActionValue& Value);
	void MoveY(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void SpawnEffects(const FVector& Location) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveRightAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	UArrowComponent* DirectionArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterialInstanceDynamic* TargetMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	float MovementForce = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UNiagaraSystem* HitVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	USoundWave* HitSound;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UStaticMeshComponent* GetMesh() const { return Mesh; }

private:
	UFUNCTION()    
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	void UpdateArrow(float DeltaSeconds);

	float CurrentVelocitySize = 0.0f;
};
