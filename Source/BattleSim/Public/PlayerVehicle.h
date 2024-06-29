// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicle.h"
#include "PlayerVehicle.generated.h"

/**
 * @brief ����ؾ��࣬�̳����ؾ���
 */
UCLASS()
class BATTLESIM_API APlayerVehicle : public AVehicle
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	APlayerVehicle();

};
