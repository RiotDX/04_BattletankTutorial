// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretComponent) {
	TankAimingComponent->SetTurretReference(TurretComponent);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	if(!ProjectileBlueprint) {
		UE_LOG(LogTemp, Error, TEXT("Error, projectile blueprint variable not assigned"))
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation) {
	
	TankAimingComponent->AimAt(HitLocation, LaunchVelocity);

}

void ATank::Fire() {
	if (!ProjectileBlueprint) { return; }

	bool isReloaded = (GetWorld()->TimeSeconds - LastFireTime) > ReloadTimeSeconds;
	if (barrel && isReloaded){
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			barrel->GetSocketLocation(FName("firingPoint")),
			barrel->GetSocketRotation(FName("firingPoint")));

		projectile->LaunchProjectile(LaunchVelocity);
		LastFireTime = GetWorld()->TimeSeconds;
	}
}

