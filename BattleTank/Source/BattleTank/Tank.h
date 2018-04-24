// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Tank.generated.h"

class AProjectile;

/// Declares a new delegate type called FMyDelegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, 
		AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(VisibleAnywhere, Category = "Statistics")
		int32 CurrentHealth = 100;
	
	UPROPERTY(EditDefaultsOnly, Category = "Statistics")
		int32 MaxHealth = 100;

public:

	// Returns current health as a percentage (0-1)
	UFUNCTION(BlueprintPure, Category = "CustomStatistics")
		float GetHealthPercent() const;

	// Declare a new delegate variable of type FMyDelegate for other classes to subscribe to.
	FMyDelegate OnDeath;
};
