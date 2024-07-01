// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UEController.h"
#include "MyPlayerController.h"
#include "BattleSimGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESIM_API ABattleSimGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	UEController* gameController;
	~ABattleSimGameModeBase();

public:
	virtual void BeginPlay() override;
	ABattleSimGameModeBase();
	virtual void Tick(float DeltaTime) override;
};
