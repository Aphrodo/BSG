// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Pickup.h"
#include "Item.generated.h"

/**
 * 
 */


 //// Items ///////
USTRUCT(BlueprintType)
struct FItem:public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
		
	FItem();

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		UTexture2D* Thumbnail; // Texture 2D to show on the UI

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FText Action; // 如何使用对象


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class APickup> ItemPickup; // 拾取类型对象

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Item")
		int32 Amount; // Number of items in inventory

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Item")
		int32 LimitedAmount;// Limited Number of items in inventory

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanBeUsed; // 是否可以被使用

	bool operator == (const FItem& Item) const { // 重载==，如果他们ID相同，就说明他们两个是属于同一种类型。
		return ItemID == Item.ItemID;
	}

};


UCLASS(BlueprintType)
class UItemData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
		TArray<FItem> Data;
};


//// Items ///////

class BS2_API Item
{
public:
	Item();
	~Item();
};
