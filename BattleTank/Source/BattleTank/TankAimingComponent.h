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

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	/// FString myTankName;

	UTankBarrel* barrel = nullptr;

	UTankTurret* turret = nullptr;

	void MoveBarrel(FVector AimDirection);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState aimState = EFiringState::Reloading;

public:	

	void AimAt(FVector WorldTarget, float velocity);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* Barrel, UTankTurret* Turret);
};
