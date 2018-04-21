// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle) {

	auto ForceApplied = GetForwardVector() * throttle * TrackMaxDriveForce;
	auto ForceLocation = GetComponentLocation();
	auto rootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	rootComponent->AddForceAtLocation(ForceApplied, ForceLocation);
}
