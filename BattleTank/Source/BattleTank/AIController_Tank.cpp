// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController_Tank.h"

void AAIController_Tank::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	ControlledTank = Cast<ATank>(GetPawn());
	
	if(!ControlledTank)
		Destroy();

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if(!PlayerTank)
		UE_LOG(LogTemp, Error, TEXT("No player tank found."))
}

void AAIController_Tank::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (!ControlledTank) {
		Destroy();
	}
	
	if(!PlayerTank) PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if(PlayerTank) {
		MoveToActor(PlayerTank, AcceptanceRadius);

		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire();
	} 
	
	return;

}

