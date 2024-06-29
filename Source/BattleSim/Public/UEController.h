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
 * @brief ���ڿ�����Ϸ�е������ؾߣ��������������ؾߵ�״̬��ģ����н���
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

	/*@brief ��GameMode��Tick���ü���*/
	void Tick(float DeltaTime);
	void BeginPlay();
	~UEController();
};
