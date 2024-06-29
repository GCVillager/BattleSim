// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerVehicle.h"
#include "EnemyTank.h"
#include "EnemyCar.h"
#include "EnemyPlane.h"
#include "TargetManager.h"
#include "GenLandscape.h"
#include "Engine/World.h"

/**
 * @brief 用于控制游戏中的所有载具，并且与计算各个载具的状态的模块进行交互
 */
class BATTLESIM_API UEController
{

private:
	APlayerVehicle* playerVehicle;
	UWorld* world;
	TargetManager* targetManager;

	TArray<AEnemyVehicle*> enemyVehicleList;
public:
	UEController();
	void setWorld(UWorld* world);
	void update();

	/*@brief 被GameMode的Tick调用即可*/
	void Tick(float DeltaTime);
	void BeginPlay();
	~UEController();
};
