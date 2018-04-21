// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), Category = Custom, hidecategories = ("Physics"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeedDegrees);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Properties)
		float MaxDegreesPerSecond = 10;
	
	UPROPERTY(EditDefaultsOnly, Category = Properties)
		float MinRotationDegrees = 0;

	UPROPERTY(EditDefaultsOnly, Category = Properties)
		float MaxRotationDegrees = 40;
};
