// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeedDegrees) {

	RelativeSpeedDegrees = FMath::Clamp<float>(RelativeSpeedDegrees, -1, 1);
	
	auto ElevationChange = RelativeSpeedDegrees * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinRotationDegrees, MaxRotationDegrees);

	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));

}
