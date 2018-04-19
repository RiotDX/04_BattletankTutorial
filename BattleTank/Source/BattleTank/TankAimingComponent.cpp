// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/// myTankName = GetOwner()->GetName();
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector WorldTarget, float velocity) {

	if (!barrel) { return; }

	FVector outLaunchVelocity;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		outLaunchVelocity,
		barrel->GetSocketLocation(FName("firingPoint")),
		WorldTarget,
		velocity,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(bHaveAimSolution) {
		auto aimDirection = outLaunchVelocity.GetSafeNormal();

		MoveBarrel(aimDirection);
	}

}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	auto BarrelRotator = barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	barrel->Elevate(5);
}