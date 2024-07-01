// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Camera/CameraActor.h"

#include "string"

#include "Vehicle.generated.h"

enum VehicleStatus
{
	ALIVE, TARGETED, DEAD
};

/**
* @brief 游戏载具类，派生出所有我方和敌方的载具
* @brief 通过设置载具的位置，旋转，以及更新载具的信息，来实现游戏中的载具的显示
*
*/
UCLASS()
class BATTLESIM_API AVehicle : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* infoWidgetComponent;

	void setTextColor(FLinearColor color);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*@brief 设置载具的位置和旋转*/
	void setLocation(FVector location, FRotator rotation);

	/*@brief !!应当每帧调用!! 每帧更新载具的信息，让信息面板始终朝向摄像机*/
	void updateWidget();

	/*@brief 设置载具信息的文本*/
	virtual void setInfo(std::string);
	/*@brief 目标id，其中我方单位为0*/
	int id;
};
