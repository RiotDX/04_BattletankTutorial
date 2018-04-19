// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "AIController_Tank.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AAIController_Tank : public AAIController
{
	GENERATED_BODY()

private:

	ATank* PlayerTank;
	
	ATank* GetControlledTank() const;
	
	ATank* ControlledTank;
	
	void BeginPlay() override;

	ATank* GetPlayerTank() const;

	virtual void Tick(float DeltaTime) override;

public:

};
