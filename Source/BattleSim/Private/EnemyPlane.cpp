// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPlane.h"

AEnemyPlane::AEnemyPlane() :AEnemyVehicle()
{
	//set up the mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/EnemyPlane.EnemyPlane'"));

	MeshComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));

	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}