// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
	bGenerateOverlapEvents = true;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	myRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {

	DriveTrack();
	ApplySidewaysForce();

	currentThrottle = 0;
}

// Calculate and apply a counter force to prevent tank from slipping sideways
void UTankTrack::ApplySidewaysForce() {
	auto slipSpeed =FVector::DotProduct( GetComponentVelocity(), GetRightVector());
	auto correctionAccel = -slipSpeed / GetWorld()->DeltaTimeSeconds * GetRightVector();

	if (!ensure(myRoot)) { return; }

	auto myMass = myRoot->GetMass();
	auto correctionForce = myMass * correctionAccel / 2; // Div by two because there are two tracks

	myRoot->AddForce(correctionForce);
}

void UTankTrack::DriveTrack() {
	auto ForceApplied = GetForwardVector() * currentThrottle * TrackMaxDriveForce;
	auto ForceLocation = GetComponentLocation();
	auto rootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	rootComponent->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::SetThrottle(float throttle) {
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

