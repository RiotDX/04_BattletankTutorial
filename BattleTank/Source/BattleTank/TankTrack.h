// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/*
 * TankTrack is used to set maximum driving force and apply planar force to the Tank parent.
 */

UCLASS(meta = (BlueprintSpawnableComponent), Category = Custom)
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:

	UTankTrack();

	void BeginPlay() override;

	void ApplySidewaysForce();

	void DriveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse, const FHitResult& Hit);
	
	UStaticMeshComponent* myRoot = nullptr;

	float currentThrottle = 0;

public:
	
	// Sets throttle percentage (0-1) based on amount of trigger input
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float throttle);

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Drive)
		float TrackMaxDriveForce = 40000000.0;  // 40 tonne tank, 1g acceleration. F=MA
	
};
