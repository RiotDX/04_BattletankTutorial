// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController_Tank.h"

void AAIController_Tank::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	ControlledTank = GetControlledTank();
	
	if(!ControlledTank)
		/// UE_LOG(LogTemp, Warning, TEXT("AI Controller possessing tank %s."), *ControlledTank->GetName())
	///else {
		Destroy();
	///}

	PlayerTank = GetPlayerTank();

	if(!PlayerTank)
		UE_LOG(LogTemp, Error, TEXT("No player tank found."))
}

void AAIController_Tank::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if(GetPlayerTank()) {
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}

}

ATank * AAIController_Tank::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

ATank* AAIController_Tank::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

