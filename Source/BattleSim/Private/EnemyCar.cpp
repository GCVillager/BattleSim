// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCar.h"

AEnemyCar::AEnemyCar() :AEnemyVehicle()
{
	//set up the mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/EnemyCar.EnemyCar'"));

	MeshComponent->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}