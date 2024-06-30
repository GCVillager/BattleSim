// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPlane.h"

AEnemyPlane::AEnemyPlane() :AEnemyVehicle()
{
	//set up the mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/EnemyPlane.EnemyPlane'"));

	float scale = 0.2f;
	MeshComponent->SetRelativeScale3D(FVector(scale, scale, scale));

	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}

	float widgetScale = 0.85f;
	infoWidgetComponent->SetRelativeScale3D(FVector(widgetScale / scale, widgetScale / scale, widgetScale / scale));
}