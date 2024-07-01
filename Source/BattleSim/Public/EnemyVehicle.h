// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicle.h"
#include <string>
#include "EnemyVehicle.generated.h"


/**
 * @brief 敌方载具的UE类，继承自Vehicle，派生出敌方坦克、飞机、装甲车等类
 * @brief 具有状态属性（活动，被标记，死亡），可设置，会影响在UE中的显示
 * @brief 具有设置信息的方法，用于在UE中显示信息
 */
UCLASS()
class BATTLESIM_API AEnemyVehicle : public AVehicle
{
	GENERATED_BODY()

protected:
	VehicleStatus status;
public:
	AEnemyVehicle();
	void setStatus(VehicleStatus newStatus);
	VehicleStatus getStatus();
	void BeginPlay() override;
	virtual void setInfo(std::string info);
	void destroy();
};

