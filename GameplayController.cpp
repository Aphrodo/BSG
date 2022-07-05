// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayController.h"
#include "GenericPlatform/GenericPlatformMath.h"

AGameplayController::AGameplayController() {
	InventorySlotLimit = 12;
	
	for (int32 i = 0; i < InventorySlotLimit; i++) {
		IdleIndex.HeapPush(i);
	}
}

void AGameplayController::Interact()
{
	// 按键一按下，如果我们当前识别到了物体，那么就调用物体的交互函数。
	if (CurrentInteractable) {
		CurrentInteractable->Interact(this);
	}
}

void AGameplayController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//将按键与交互函数绑定
	InputComponent->BindAction("Interact", IE_Pressed, this, &AGameplayController::Interact);
}

bool AGameplayController::AddItem(FName ID,int32 Number)
{	
	//从datatable中查找item
	ABS2GameMode* GameMode = Cast<ABS2GameMode>(GetWorld()->GetAuthGameMode());
	UDataTable* ItemTable = GameMode->GetItemDB();
	FItem* ItemReadyToAdd = ItemTable->FindRow<FItem>(ID, "");

	if (ItemReadyToAdd == nullptr) {
		return false;
	}

	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemID == ID)
		{
			if (Inventory[i].Amount < Inventory[i].LimitedAmount&&Number>0) {
				if (Number <= Inventory[i].LimitedAmount - Inventory[i].Amount) {
					Inventory[i].Amount += Number;
					return true;
				}
				else {
					int32 reduction = Inventory[i].LimitedAmount - Inventory[i].Amount;
					Number -= reduction;
					Inventory[i].Amount = Inventory[i].LimitedAmount;
				}
			}	
			
		}
	}

	if (Inventory.Num()==InventorySlotLimit) {
		UE_LOG(LogTemp, Warning, TEXT("Inventory is full: %d / %d "), Inventory.Num(), InventorySlotLimit);
		return false;
	}

	while (Number > 0 && Inventory.Num() < InventorySlotLimit) {
		Inventory.Add(*ItemReadyToAdd);
		if (Number <= ItemReadyToAdd->LimitedAmount) {
			Inventory[Inventory.Num() - 1].Amount = Number;
			return true;
		}
		else {
			Inventory[Inventory.Num() - 1].Amount= Inventory[Inventory.Num() - 1].LimitedAmount;
			Number-= Inventory[Inventory.Num() - 1].LimitedAmount;
		}
	}
	
		return true;



	//以下用TmultiMap加速查找物品算子会导致空地址访问编辑器会崩溃，
	// 
	////检查已有物品数量有没有空位
	//int32 IndexReadyToUse = -1;
	//if (IndexLocation.Contains(ID)) {
	//	TArray<int32> tempIndex;
	//	IndexLocation.MultiFind(ID, tempIndex);
	//	for (int32 i = 0; i < tempIndex.Num(); i++) {
	//		if (Inventory[tempIndex[i]].Amount <= Inventory[tempIndex[i]].LimitedAmount - Amount) {
	//			IndexReadyToUse = tempIndex[i];
	//			Inventory[tempIndex[i]].Amount += Amount;
	//			return true;
	//		}
	//	}
	//	
	//}

	////检查物品栏空位
	//if (IdleIndex.Num() == 0) {
	//	UE_LOG(LogTemp, Warning, TEXT("Inventory is full: %d / %d "), Inventory.Num(), InventorySlotLimit);
	//	return false;
	//}

	//IdleIndex.HeapPop(IndexReadyToUse);
	//if (IndexReadyToUse >= 0 && IndexReadyToUse <= InventorySlotLimit) {
	//	Inventory.Insert(*ItemReadyToAdd, IndexReadyToUse);
	//	Inventory[IndexReadyToUse].Amount = Amount;
	//	IndexLocation.AddUnique(ItemReadyToAdd->ItemID, IndexReadyToUse);
	//	return true;
	//}
	
	
}

bool AGameplayController::RemoveItem(FName ItemID, int32 RemovedIndex)
{
	return false;
}
