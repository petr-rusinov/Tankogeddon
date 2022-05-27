// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* sceneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneCpm;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Mesh"));
	Mesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void ACannon::Fire()
{
	if (!ReadyToFire)
		return;
	ReadyToFire = false;
	if (CurrentBulletsNum == 0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "No Bullets Left!");
		return;
	}
	else
		--CurrentBulletsNum;
	UE_LOG(LogTemp, Warning, TEXT("Bullets left: %d of %d"), CurrentBulletsNum, FireTotalBullets);
	if (Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - Projectile");
		SpawnProjectile();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - Trace");
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSpecial()
{
	if (!ReadyToFire)
		return;
	ReadyToFire = false;
	if (CurrentBulletsNum == 0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "No Bullets Left!");
		return;
	}
	else
		--CurrentBulletsNum;
	UE_LOG(LogTemp, Warning, TEXT("Bullets left: %d of %d"), CurrentBulletsNum, FireTotalBullets);
	ReadyToSeries = true;
}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}

void ACannon::Reload()
{
	GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - Reload");

	if (projectilesInSeries == 0)
		projectilesInSeries = FireSeriesProjectileNumber;
	ReadyToFire = true;
	ReadyToNextProjectile = true;
}

void ACannon::NextProjectle()
{
	ReadyToNextProjectile = true;
}

void ACannon::Tick(float DeltaTime)
{
	if (!ReadyToSeries)
		return;
	if (!ReadyToNextProjectile)
		return;
	ReadyToNextProjectile = false;

	if (projectilesInSeries > 0)
	{
		--projectilesInSeries;
		if (Type == ECannonType::FireProjectile)
		{
			GEngine->AddOnScreenDebugMessage(projectilesInSeries, 1, FColor::Red, "FireSpecial - Projectile");
			SpawnProjectile();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(projectilesInSeries, 1, FColor::Red, "FireSpecial - Trace");
		}
		GetWorld()->GetTimerManager().SetTimer(SeriesTimerHandle, this, &ACannon::NextProjectle, 1 / FireSeriesRate, false);
	}
	else
	{
		ReadyToSeries = false;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
	}

}

void ACannon::SpawnProjectile()
{
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	if (projectile)
		projectile->Start();

}


