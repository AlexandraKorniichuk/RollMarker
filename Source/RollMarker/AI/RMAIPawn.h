// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RMAIPawn.generated.h"

class UNiagaraSystem;
class UBehaviorTree;

UCLASS()
class ROLLMARKER_API ARMAIPawn : public APawn
{
	GENERATED_BODY()

public:
	ARMAIPawn();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterialInstanceDynamic* DynamicMaterial;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetDynamicMaterial(FLinearColor Color);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)    
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UMaterialInstanceDynamic* GetDynamicMaterial() const { return DynamicMaterial; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UStaticMeshComponent* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ColorMesh(FLinearColor Color);

	/** 
	 *	Try to color the OtherPawn to the TargetColor.
	 *	@param	OtherPawn	Pawn that must be colored
	 *	@param RequiredColor Color of this pawn that requires to color OtherPawn
	 *	@param TargetColor	If RequiredColor is correct, this color will be set to OtherPawn
	 *	@return				Returns true, if the coloring was successful, 
	 */
	UFUNCTION(BlueprintCallable)
	bool TryColorToTargetColor(ARMAIPawn* OtherPawn, FLinearColor RequiredColor, FLinearColor TargetColor);

	FLinearColor GetCurrentColor() const { return CurrentColor; }
	
private:
	FLinearColor CurrentColor;
};
