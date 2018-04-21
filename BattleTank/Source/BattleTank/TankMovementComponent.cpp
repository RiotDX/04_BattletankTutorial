// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackIn, UTankTrack* rightTrackIn) {
	if (!leftTrackIn || !rightTrackIn) {
		UE_LOG(LogTemp, Error, TEXT("Initialise Tank Movement failed due to missing inputs."))
			return;
	}
	LeftTrack = leftTrackIn;
	RightTrack = rightTrackIn;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	const auto AIMoveIntent = MoveVelocity.GetSafeNormal();
	const auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(AIMoveIntent, TankForward));
	IntendTurnRight(FVector::CrossProduct(TankForward, AIMoveIntent).Z);
}


