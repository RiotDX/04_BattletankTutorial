// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), Category = Custom, hidecategories = ("Physics"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Input values are clamped from -1 to +1 which is multiplied by max speed for rotation.
	void Rotate(float RelativeSpeedDegrees);

private:
	UPROPERTY(EditAnywhere, Category = Properties)
		float MaxDegreesPerSecond = 20;
	
	
};
