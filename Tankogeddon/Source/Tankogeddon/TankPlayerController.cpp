// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPawn.h"
#include "TankPlayerController.h"


ATankPlayerController::ATankPlayerController()
{
}
void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("Rotate", this, &ATankPlayerController::Rotate);
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
}
void ATankPlayerController::MoveForward(float AxisValue)
{
	TankPawn->MoveForward(AxisValue);
}

void ATankPlayerController::Rotate(float value)
{
	TankPawn->Rotate(value);
}
