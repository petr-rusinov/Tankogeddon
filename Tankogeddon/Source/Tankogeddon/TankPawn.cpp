// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

DECLARE_LOG_CATEGORY_EXTERN(TankLog, All, All);
DEFINE_LOG_CATEGORY(TankLog);
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
	CurrentRightAxisValue = GetActorRotation().Yaw;
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

	//Rotation
	FRotator currentRotation = GetActorRotation();

	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, _targetRotateValue, InterpolationKey);
	currentRotation.Yaw += CurrentRightAxisValue * DeltaTime * RotationSpeed;
	SetActorLocationAndRotation(movePosition, FQuat(currentRotation));

	//UE_LOG(LogTemp, Warning, TEXT("CurrentRightAxisValue = %f, _targetRotateValue = %f"),
	//	CurrentRightAxisValue, _targetRotateValue);

}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

