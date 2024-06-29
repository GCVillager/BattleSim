// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"

AEnemyTank::AEnemyTank() :AEnemyVehicle()
{
	//set up the mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/EnemyTank.EnemyTank'"));

	MeshComponent->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}