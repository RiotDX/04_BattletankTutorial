// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) {
	barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	myTankName = GetOwner()->GetName();
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector WorldTarget, float velocity) {
	///UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s."), *myTankName, *WorldTarget.ToString())
	///auto BarrelLocation = barrel->GetComponentLocation();
	if (!barrel) { return; }

	FVector outLaunchVelocity;

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		barrel->GetSocketLocation(FName("firingPoint")),
		WorldTarget,
		velocity,
		false,
		0.,
		0.,
		ESuggestProjVelocityTraceOption::DoNotTrace
		)) {
		
	}

		auto aimDirection = outLaunchVelocity.GetSafeNormal();
}

