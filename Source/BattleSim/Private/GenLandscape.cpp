// Fill out your copyright notice in the Description page of Project Settings.


#include "GenLandscape.h"

// Sets default values
AGenLandscape::AGenLandscape()
{
	//create mesh component and set as root
	TerrainMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TerrainMesh"));
	RootComponent = TerrainMesh;
	//create and set material
	Material = CreateDefaultSubobject<UMaterialInterface>(TEXT("Material"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass'"));
	if (MaterialAsset.Succeeded())
	{
		Material = MaterialAsset.Object;
		TerrainMesh->SetMaterial(0, Material);
	}
	
	map = new double[500][500];

}

// Called when the game starts or when spawned
void AGenLandscape::BeginPlay()
{
	Super::BeginPlay();
	//generate terrain when game starts
	GenerateTerrain();
}


void AGenLandscape::GenerateTerrain()
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;

	//generate vertices
	for (int32 Y = 0; Y < GridSize; Y++)
	{
		for (int32 X = 0; X < GridSize; X++)
		{
			//generate height,use perlin noise
			float Height = utils::PerlinNoise2D(X, Y) * HeightScale;
			//
			Vertices.Add(FVector(X * TileSize, Y * TileSize, Height));
			Normals.Add(FVector(0, 0, 1));
			UVs.Add(FVector2D(X / (float)GridSize*10.0, Y / (float)GridSize)*100.0);
			map[X][Y] = Height;
		}
	}

	//generate triangles
	for (int32 Y = 0; Y < GridSize - 1; Y++)
	{
		for (int32 X = 0; X < GridSize - 1; X++)
		{
			int32 TopLeft = X + Y * GridSize;
			int32 TopRight = (X + 1) + Y * GridSize;
			int32 BottomLeft = X + (Y + 1) * GridSize;
			int32 BottomRight = (X + 1) + (Y + 1) * GridSize;

			Triangles.Add(TopLeft);
			Triangles.Add(BottomLeft);
			Triangles.Add(TopRight);

			Triangles.Add(TopRight);
			Triangles.Add(BottomLeft);
			Triangles.Add(BottomRight);
		}
	}
	TerrainMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}


AGenLandscape::~AGenLandscape()
{
	delete[] map;
}