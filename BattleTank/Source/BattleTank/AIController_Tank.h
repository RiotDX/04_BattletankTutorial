// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "AIController_Tank.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API AAIController_Tank : public AAIController
{
	GENERATED_BODY()

private:

	ATank* PlayerTank;

	UTankAimingComponent* AimingComponent;
	
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float AcceptanceRadius = 4000;

};
