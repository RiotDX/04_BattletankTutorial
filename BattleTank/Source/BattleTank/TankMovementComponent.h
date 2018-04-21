// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 *  Responsible for indirectly control of the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Custom")
		void IntendMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = "Custom")
		void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTrack* leftTrackIn, UTankTrack* rightTrackIn);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	// Called from pathfinding logic on AI Controllers
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
};
