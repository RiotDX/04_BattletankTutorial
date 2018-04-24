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
	if(ammoValue <= 0) {
		aimState = EFiringState::OutOfAmmo;
	} else if((GetWorld()->TimeSeconds - LastFireTime) < ReloadTimeSeconds) {
		aimState = EFiringState::Reloading;
	} else if (IsBarrelMoving()) {
		aimState = EFiringState::Aiming;
	} else {
		aimState = EFiringState::LockedOn;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const { return aimState; }
int32 UTankAimingComponent::GetAmmunitionCount() const { return ammoValue; }

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

	auto yaw = DeltaRotator.Yaw;
	// Take shortest path
	if (FMath::Abs(yaw) < 180)
		turret->Rotate(yaw);
	else
		turret->Rotate(-yaw);
}

void UTankAimingComponent::Fire() {
	if (!ensure(ProjectileBlueprint && barrel)) { return; }
	
	if (aimState == EFiringState::Aiming || aimState == EFiringState::LockedOn) {
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
		barrel->GetSocketLocation(FName("firingPoint")),
		barrel->GetSocketRotation(FName("firingPoint")));

		projectile->LaunchProjectile(launchSpeed);
		LastFireTime = GetWorld()->TimeSeconds;
		ammoValue--;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(barrel)) { return false; }
	return !aimDirection.Equals(barrel->GetForwardVector(), 0.1);
}
