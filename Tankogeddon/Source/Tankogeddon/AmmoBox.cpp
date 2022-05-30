// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"
#include "TankPawn.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Scene;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
	Mesh->SetCollisionProfileName(TEXT("OverlapAll"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(true);

}


void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ATankPawn* PlayerPawn = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//ATankPawn* Tank = Cast<ATankPawn>(OtherActor);
	//if (Tank)
	//{
	//	Tank->SetupCannon(CannonClass);
	//	Destroy();
	//}
	UE_LOG(LogTemp, Warning, TEXT("%s collided with %s. "), *GetName(), *OtherActor->GetName());

	ATankPawn* playerPawn = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (OtherActor == playerPawn)
	{
		playerPawn->SetupCannon(CannonClass);
		Destroy();
	}
}

