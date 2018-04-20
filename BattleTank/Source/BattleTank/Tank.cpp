// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Kaboom!"))

	if (!barrel) { return; }

	auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
		barrel->GetSocketLocation(FName("firingPoint")), 
		barrel->GetSocketRotation(FName("firingPoint")));

	projectile->LaunchProjectile(LaunchVelocity);
}

