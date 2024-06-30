// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"

AEnemyTank::AEnemyTank() :AEnemyVehicle()
{
	//set up the mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/EnemyTank.EnemyTank'"));
	float scale = 0.3f;
	MeshComponent->SetRelativeScale3D(FVector(scale,scale,scale));

	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
	//set widget scale
	float widgetScale = 0.85f;
	infoWidgetComponent->SetRelativeScale3D(FVector(widgetScale / scale, widgetScale / scale, widgetScale / scale));
}