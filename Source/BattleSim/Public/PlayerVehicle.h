// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicle.h"
#include "PlayerVehicle.generated.h"

/**
 * @brief 玩家载具类，继承自载具类
 */
UCLASS()
class BATTLESIM_API APlayerVehicle : public AVehicle
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	APlayerVehicle();

};
