// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProceduralMeshComponent.h"
#include "GenLandscape.generated.h"


/*
* @brief 地形actor类，在游戏开始时生成地形
*/
UCLASS()
class BATTLESIM_API AGenLandscape : public AActor
{ 
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGenLandscape();

protected:
	~AGenLandscape();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* TerrainMesh;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material;

	UPROPERTY(VisibleAnywhere, Category = "Terrain")
	int32 GridSize = 500;

	UPROPERTY(VisibleAnywhere, Category = "Terrain")
	float TileSize = 15.0f;

	UPROPERTY(VisibleAnywhere, Category = "Terrain")
	float HeightScale = 300.0f;

	void GenerateTerrain();
	float PerlinNoise2D(float X, float Y) const;
public:	

	double(*map)[500];
};
