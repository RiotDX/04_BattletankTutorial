// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController_Tank.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void AAIController_Tank::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
	
	if(!GetPawn()) {
		Destroy();
		return;
	}

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if(!ensure(PlayerTank))
		UE_LOG(LogTemp, Error, TEXT("No player tank found."))
}

void AAIController_Tank::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (!ensure(GetPawn())) {
		Destroy();
	}
	
	if(!PlayerTank) PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if(PlayerTank) {
		MoveToActor(PlayerTank, AcceptanceRadius);

		if (!ensure(AimingComponent)) { return; }
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if(AimingComponent->GetFiringState() == EFiringState::LockedOn)
		AimingComponent->Fire();
	} 
	
	return;

}

void AAIController_Tank::SetPawn(APawn* InPawn){
	Super::SetPawn(InPawn);
	if(InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		
		// Subscribe to PossessedTank's Delegate called OnDeath, using this function VV
		PossessedTank->OnDeath.AddUniqueDynamic(this, &AAIController_Tank::OnTankDeath);
	}
}

void AAIController_Tank::OnTankDeath() {
	GetPawn()->DetachFromControllerPendingDestroy();
}
