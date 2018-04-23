// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay() {
	
	Super::BeginPlay();

	if (!ProjectileBlueprint) {
		UE_LOG(LogTemp, Error, TEXT("Error, projectile blueprint variable not assigned"))
	}
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	if((GetWorld()->TimeSeconds - LastFireTime) < ReloadTimeSeconds) {
		aimState = EFiringState::Reloading;
	} else if (IsBarrelMoving()) {
		aimState = EFiringState::Aiming;
	} else {
		aimState = EFiringState::LockedOn;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* Barrel, UTankTurret* Turret) {
	if (!Turret) { return; }
	turret = Turret;

	if (!Barrel) { return; }
	barrel = Barrel;

}

void UTankAimingComponent::AimAt(FVector WorldTarget) {

	if (!barrel) { return; }

	FVector outLaunchVelocity;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		outLaunchVelocity,
		barrel->GetSocketLocation(FName("firingPoint")),
		WorldTarget,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(bHaveAimSolution) {
		aimDirection = outLaunchVelocity.GetSafeNormal();

		MoveBarrel(aimDirection);
	}

}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	if (!ensure(barrel && turret)) { return; }

	auto BarrelRotator = barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	barrel->Elevate(DeltaRotator.Pitch);
	turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire() {
	if (aimState != EFiringState::Reloading) {
		if (!ensure(ProjectileBlueprint && barrel)) { return; }
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
		barrel->GetSocketLocation(FName("firingPoint")),
		barrel->GetSocketRotation(FName("firingPoint")));

		projectile->LaunchProjectile(launchSpeed);
		LastFireTime = GetWorld()->TimeSeconds;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(barrel)) { return false; }
	return !aimDirection.Equals(barrel->GetForwardVector(), 0.1);
}