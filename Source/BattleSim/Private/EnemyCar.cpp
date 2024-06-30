// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCar.h"

AEnemyCar::AEnemyCar() :AEnemyVehicle()
{
	//set up the mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/EnemyCar.EnemyCar'"));

	float scale = 0.55f;
	MeshComponent->SetRelativeScale3D(FVector(scale, scale, scale));

	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}

	float widgetScale = 0.85f;
	infoWidgetComponent->SetRelativeScale3D(FVector(widgetScale / scale, widgetScale / scale, widgetScale / scale));
}