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
	PrimaryComponentTick.bCanEverTick = false;

	if (!ProjectileBlueprint) {
		UE_LOG(LogTemp, Error, TEXT("Error, projectile blueprint variable not assigned"))
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
		auto aimDirection = outLaunchVelocity.GetSafeNormal();

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
	if (!ensure(ProjectileBlueprint && barrel)) { return; }
	bool isReloaded = (GetWorld()->TimeSeconds - LastFireTime) > ReloadTimeSeconds;

	if (isReloaded){
	auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
	barrel->GetSocketLocation(FName("firingPoint")),
	barrel->GetSocketRotation(FName("firingPoint")));

	projectile->LaunchProjectile(launchSpeed);
	LastFireTime = GetWorld()->TimeSeconds;
	}
}