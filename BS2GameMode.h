// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BS2GameMode.generated.h"

UCLASS(minimalapi)
class ABS2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABS2GameMode();

	class UDataTable* GetItemDB() const { return ItemDB; }
protected:

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ItemDB;
};



