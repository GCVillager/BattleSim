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
* @brief ��Ϸ�ؾ��࣬�����������ҷ��͵з����ؾ�
* @brief ͨ�������ؾߵ�λ�ã���ת���Լ������ؾߵ���Ϣ����ʵ����Ϸ�е��ؾߵ���ʾ
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

	/*@brief �����ؾߵ�λ�ú���ת*/
	void setLocation(FVector location, FRotator rotation);

	/*@brief !!Ӧ��ÿ֡����!! ÿ֡�����ؾߵ���Ϣ������Ϣ���ʼ�ճ��������*/
	void updateWidget();

	/*@brief �����ؾ���Ϣ���ı�*/
	virtual void setInfo(std::string);
	/*@brief Ŀ��id�������ҷ���λΪ0*/
	int id;
};
