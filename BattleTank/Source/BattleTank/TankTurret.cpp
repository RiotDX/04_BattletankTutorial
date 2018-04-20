// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeedDegrees) {
	RelativeSpeedDegrees = FMath::Clamp<float>(RelativeSpeedDegrees, -1, 1);

	auto RotationChange = RelativeSpeedDegrees * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}
