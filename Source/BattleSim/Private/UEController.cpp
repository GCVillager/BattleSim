// Fill out your copyright notice in the Description page of Project Settings.
#pragma warning(disable:4456)

const int TILE_SIZE = 15;

#include "UEController.h"

#include <algorithm>


std::string round(float x,int n)
{
	std::string tmp = std::to_string(x);
	int pos = tmp.find('.');
	if (pos == -1)
	{
		tmp += ".";
		for (int i = 0; i < n; i++)
			tmp += "0";
		return tmp;
	}
	else if (tmp.size() - pos - 1 < n)
	{
		for (int i = 0; i < n - (tmp.size() - pos - 1); i++)
			tmp += "0";
		return tmp;
	}
	return tmp.substr(0, pos + n + 1);
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
	playerVehicle->setInfo("Our Unit");
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
	double sideAngle = ourunit->getSideAngle();
	if (verticalAngle < 0)
		verticalAngle = 360 + verticalAngle;
	//将二元的旋转角度转换为FRotator
	FRotator rotator = FRotator(verticalAngle, horizontalAngle+90,sideAngle);
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
		else if (target.markedKilled && enemyVehicleList[i]->getStatus() != TARGETED)
		{
			enemyVehicleList[i]->setStatus(TARGETED);
			ABomb* bomb = world->SpawnActor<ABomb>(ABomb::StaticClass());
			bomb->init(playerVehicle, enemyVehicleList[i]);
		}
		Position pos = target.getPosition();
		double verticalAngle = target.getVerticalAngle();
		double horizontalAngle = target.getHorizontalAngle();
		double sideAngle = target.getSideAngle();
		//将二元的旋转角度转换为FRotator
		if (verticalAngle < 0)
			verticalAngle = 360 + verticalAngle;
		FRotator rotator = FRotator(verticalAngle, horizontalAngle+90,sideAngle);
		//将坐标转换为FVector
		FVector location = FVector(pos.x*TILE_SIZE, pos.y*TILE_SIZE, pos.z*TILE_SIZE);
		//将坐标和旋转角度赋值给enemyVehicleList[i]
		enemyVehicleList[i]->SetActorLocationAndRotation(location, rotator);
		enemyVehicleList[i]->updateWidget();
		enemyVehicleList[i]->setInfo(std::to_string(target.getLevel() + 1) + ":" + round(target.getScore(), 2));
	}
	AMyPlayerController* playerController = Cast<AMyPlayerController>(world->GetFirstPlayerController());
	playerController->changeTip(FString(round(targetManager->getAccuracy(),3).c_str()));
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