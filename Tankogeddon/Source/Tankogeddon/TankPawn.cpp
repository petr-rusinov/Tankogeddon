// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Body"));
	RootComponent = BodyMesh;
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void ATankPawn::MoveForward(float AxisValue)
{
	_targetForwardAxisValue = AxisValue;
}

void ATankPawn::Rotate(float value)
{
	_targetRotateValue = value;
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = currentLocation + forwardVector * MoveSpeed * _targetForwardAxisValue * DeltaTime;
	//SetActorLocation(movePosition, true);

	//Поворот
	FRotator currentRotation = GetActorRotation();
	currentRotation.Yaw += _targetRotateValue * RotationSpeed;
	
	SetActorLocationAndRotation(movePosition, FQuat(currentRotation));

}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

