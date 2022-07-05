// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interactable.h"
#include "BS2GameMode.h"
#include "Item.h"
#include "GameplayController.generated.h"

/**
 * 
 */
UCLASS()
class BS2_API AGameplayController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGameplayController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class AInteractable* CurrentInteractable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FItem> Inventory;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 InventorySlotLimit;// x格背包+x快捷物品栏

	TArray<int32> IdleIndex;//记录物品栏剩余空格，用堆操作处理（小根堆），


	TMultiMap<FName, int32> IndexLocation;

protected:
	// 物品交互操作
	void Interact();

	virtual void SetupInputComponent() override;
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool AddItem(FName ID,int32 Number);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool RemoveItem(FName ItemID, int32 RemovedIndex);


	
};
