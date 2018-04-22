// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerController_Tank.h"
#include "TankAimingComponent.h"

void APlayerController_Tank::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Aiming Component not found."))
	}

}

void APlayerController_Tank::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimTowardCrosshair();
}

void APlayerController_Tank::AimTowardCrosshair() {
	FVector HitLocation;
	if(GetSightRayHitLocation(HitLocation)) {
		if (!ensure(AimingComponent)) { return; }
		AimingComponent->AimAt((HitLocation));
	}
}

bool APlayerController_Tank::GetSightRayHitLocation(FVector& OutHitLocation) const {
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	
	OutHitLocation = FVector(0.);
	return false;
}

bool APlayerController_Tank::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const {
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool APlayerController_Tank::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceMaxDistance);

	if(GetWorld()->LineTraceSingleByChannel(
	HitResult,
	StartLocation,
	EndLocation,
	ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false;
}

