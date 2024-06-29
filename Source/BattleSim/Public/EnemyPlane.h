// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyVehicle.h"
#include "EnemyPlane.generated.h"

/**
 * @brief 敌方飞机的UE类，继承自EnemyVehicle
 */
UCLASS()
class BATTLESIM_API AEnemyPlane : public AEnemyVehicle
{
	GENERATED_BODY()
public:
	AEnemyPlane();
};
