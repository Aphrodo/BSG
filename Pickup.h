// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class BS2_API APickup : public AInteractable
{
	GENERATED_BODY()
	
public:
	APickup();

	void Interact_Implementation(APlayerController* Controller) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	class UStaticMeshComponent* GetStaticMesh() const { return PickupMesh; }

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Pickup")
		void OnUsed();
protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Quantity; // Number of items 

	
		virtual FString GetInteractText() const override;
};
