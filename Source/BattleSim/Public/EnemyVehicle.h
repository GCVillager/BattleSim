// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicle.h"
#include <string>
#include "EnemyVehicle.generated.h"


/**
 * @brief �з��ؾߵ�UE�࣬�̳���Vehicle���������з�̹�ˡ��ɻ���װ�׳�����
 * @brief ����״̬���ԣ��������ǣ��������������ã���Ӱ����UE�е���ʾ
 * @brief ����������Ϣ�ķ�����������UE����ʾ��Ϣ
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

