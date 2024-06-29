// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyVehicle.h"
#include "EnemyCar.generated.h"

/**
 * @brief 敌方装甲车的UE类，继承自EnemyVehicle
 */
UCLASS()
class BATTLESIM_API AEnemyCar : public AEnemyVehicle
{
	GENERATED_BODY()
	
public:
	AEnemyCar();

};
