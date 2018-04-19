// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

// Holds parameters for barrel properties
class UTankBarrel;  /// I'm a Forward Declaration!

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	FString myTankName;

	UTankBarrel* barrel = nullptr;

	void MoveBarrel(FVector AimDirection);

public:	

	void AimAt(FVector WorldTarget, float velocity);
		
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
};
