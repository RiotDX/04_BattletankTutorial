// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "PlayerController_Tank.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API APlayerController_Tank : public APlayerController
{
	GENERATED_BODY()
	
private:
	void AimTowardCrosshair();

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
	
	UPROPERTY(EditAnywhere)
	float LineTraceMaxDistance = 1000000.;

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

public:
	
	void BeginPlay() override;

	void Tick(float deltaTime) override;
};
