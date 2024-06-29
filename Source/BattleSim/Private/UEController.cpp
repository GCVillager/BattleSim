// Fill out your copyright notice in the Description page of Project Settings.
#pragma warning(disable:4456)

const int TILE_SIZE = 15;

#include "UEController.h"

#include <algorithm>

float round(float x,int n)
{
	//保留n位小数
	return floor(x * pow(10, n) + 0.5) / pow(10, n);
}

UEController::UEController()
{

}

UEController::~UEController()
{
	delete targetManager;
}

void UEController::BeginPlay()
{
	//generate landscape
	AGenLandscape* Landscape = world->SpawnActor<AGenLandscape>(AGenLandscape::StaticClass());
	targetManager = new TargetManager();
	targetManager->initialMap(Landscape->map);
	targetManager->K = 15;
	targetManager->maxIters = 100;
	targetManager->convergenceRadius = 1e-4;
	targetManager->ready();
	playerVehicle = world->SpawnActor<APlayerVehicle>(APlayerVehicle::StaticClass());
	playerVehicle->id = 0;
	playerVehicle->setInfo("我方单位");
	update();
}

void UEController::update()
{
	OurUnit* ourunit = targetManager->getUnit();
	std::vector<Target> TargetList = targetManager->getTargetList();
	std::sort(TargetList.begin(), TargetList.end(), [](Target a, Target b) {return a.getId() < b.getId(); });

	Position pos = ourunit->getPosition();
	double verticalAngle = ourunit->getVerticalAngle();
	double horizontalAngle = ourunit->getHorizontalAngle();
	if (verticalAngle < 0)
		verticalAngle = 360 + verticalAngle;
	//将二元的旋转角度转换为FRotator
	FRotator rotator = FRotator(verticalAngle, horizontalAngle,0);
	//将坐标转换为FVector
	FVector location = FVector(pos.x*TILE_SIZE, pos.y*TILE_SIZE, pos.z*TILE_SIZE);
	//将坐标和旋转角度赋值给playerVehicle
	playerVehicle->SetActorLocationAndRotation(location, rotator);
	playerVehicle->updateWidget();

	for (int i = 0; i < TargetList.size(); i++)
	{
		Target target = TargetList[i];
		if (target.getId() >= enemyVehicleList.Num())
		{
			if (target.getType() == PLANE)
			{
				//生成飞机
				AEnemyPlane* enemyPlane = world->SpawnActor<AEnemyPlane>(AEnemyPlane::StaticClass());
				enemyVehicleList.Add(enemyPlane);
			}
			else if (target.getType() == TANK)
			{
				//生成坦克
				AEnemyTank* enemyTank = world->SpawnActor<AEnemyTank>(AEnemyTank::StaticClass());
				enemyVehicleList.Add(enemyTank);
			}
			else if (target.getType() == ARMORED_CAR)
			{
				//生成装甲车
				AEnemyCar* enemyCar = world->SpawnActor<AEnemyCar>(AEnemyCar::StaticClass());
				enemyVehicleList.Add(enemyCar);
			}
			enemyVehicleList[i]->id = target.getId();
		}
		if (target.getDeath())
		{
			enemyVehicleList[i]->setStatus(DEAD);
		}
		else if (target.markedKilled)
		{
			enemyVehicleList[i]->setStatus(TARGETED);
			//delay and set status to DEAD
			FTimerHandle TimerHandle;
			world->GetTimerManager().SetTimer(TimerHandle, [this, i]() {
				enemyVehicleList[i]->setStatus(DEAD);
				}, 3.0f, false);
		}
		Position pos = target.getPosition();
		double verticalAngle = target.getVerticalAngle();
		double horizontalAngle = target.getHorizontalAngle();
		//将二元的旋转角度转换为FRotator
		if (verticalAngle < 0)
			verticalAngle = 360 + verticalAngle;
		FRotator rotator = FRotator(verticalAngle, horizontalAngle,0);
		//将坐标转换为FVector
		FVector location = FVector(pos.x*TILE_SIZE, pos.y*TILE_SIZE, pos.z*TILE_SIZE);
		//将坐标和旋转角度赋值给enemyVehicleList[i]
		enemyVehicleList[i]->SetActorLocationAndRotation(location, rotator);
		enemyVehicleList[i]->updateWidget();
		enemyVehicleList[i]->setInfo(std::to_string(target.getLevel())+":"+std::to_string(round(target.getScore(),2)));
	}
}

void UEController::Tick(float DeltaTime)
{
	targetManager->loop(DeltaTime);
	update();
}

void UEController::setWorld(UWorld* world)
{
	this->world = world;
}