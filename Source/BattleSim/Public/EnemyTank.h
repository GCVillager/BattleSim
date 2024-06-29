// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyVehicle.h"
#include "EnemyTank.generated.h"

/**
 * @brief 敌方坦克的UE类，继承自EnemyVehicle
 */
UCLASS()
class BATTLESIM_API AEnemyTank : public AEnemyVehicle
{
	GENERATED_BODY()
	
	AEnemyTank();
};
