// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include"GameplayController.h"

APickup::APickup()
{
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh->SetupAttachment(RootComponent);

	ItemID = FName("No ID");
	Quantity = 1;
	Super::Name = "Item";
	Super::Action = "pickup";
}

void APickup::Interact_Implementation(APlayerController* Controller)
{
	Super::Interact_Implementation(Controller);

	AGameplayController* IController = Cast<AGameplayController>(Controller);
	if (IController->AddItem(ItemID, Quantity))
		Destroy();
}

void APickup::Tick(float DeltaTime)
{
	
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 30.0f;       //Scale our height by a factor of 20
	float DeltaRotation = DeltaTime * 30.0f;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

FString APickup::GetInteractText() const
{
	return FString::Printf(TEXT("%s(%d): Press E to %s"), *Name, Quantity, *Action);
}
