// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

// Aim state enum
UENUM(BlueprintType)
enum class EFiringState: uint8{ Reloading, Aiming, LockedOn };

// Holds parameters for barrel properties
class UTankBarrel;  /// I'm a Forward Declaration!
class UTankTurret;
class AProjectile;

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void BeginPlay() override;

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrel(FVector AimDirection);

	bool IsBarrelMoving();

	double LastFireTime = 0;

	FVector aimDirection = FVector(0);

	UTankBarrel* barrel = nullptr;

	UTankTurret* turret = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState aimState = EFiringState::Reloading;

public:	

	void AimAt(FVector WorldTarget);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* Barrel, UTankTurret* Turret);

	UPROPERTY(EditAnywhere, Category = "Firing")
		float launchSpeed = 5000;

	UFUNCTION(BlueprintCallable, Category = "Custom")
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeSeconds = 3;
};
