// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	RootComponent = BombMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BombMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (BombMeshAsset.Succeeded())
	{
		BombMesh->SetStaticMesh(BombMeshAsset.Object);
		//set material
		Material = CreateDefaultSubobject<UMaterialInterface>(TEXT("Material"));
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Script/Engine.Material'/Game/Materials/Bomb.Bomb'"));
		if (MaterialAsset.Succeeded())
		{
			Material = MaterialAsset.Object;
			BombMesh->SetMaterial(0, Material);
		}
	}
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float newTotalTime = totalTime + DeltaTime;
	if (newTotalTime >= timeToExplode)
	{
		//explode
		UParticleSystem* ExplosionEffect = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
		if (ExplosionEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		}
		//destroy bomb actor
		Destroy();
	}
	else
	{
		FVector newLocation = GetActorLocation();
		if (newTotalTime < upTime)
		{
			newLocation.Z = startZ + velocityZ * newTotalTime;
		}
		else if (newTotalTime < upTime+1)
		{
			newLocation.Z = startZ + velocityZ * upTime;
		}
		else
		{
			newLocation.Z = startZ + velocityZ * (upTime - (newTotalTime - upTime - 1));
		}
		float delta = DeltaTime / (timeToExplode - totalTime);
		newLocation.X = newLocation.X + (destination->GetActorLocation().X - newLocation.X) * delta;
		newLocation.Y = newLocation.Y + (destination->GetActorLocation().Y - newLocation.Y) * delta;
		SetActorLocation(newLocation);
	}
	totalTime = newTotalTime;
}



void ABomb::init(APlayerVehicle* Source, AEnemyVehicle* Destination)
{
	source = Source;
	destination = Destination;
	float h = std::max(source->GetActorLocation().Z, destination->GetActorLocation().Z)+300;
	float h1 = h - source->GetActorLocation().Z;
	float h2 = h - destination->GetActorLocation().Z;
	float t1 = (timeToExplode-1) * h1 / (h1 + h2);
	float t2 = (timeToExplode-1) * h2 / (h1 + h2);
	velocityZ = h1 / t1;
	upTime = t1;
	FVector newLocation = source->GetActorLocation();
	SetActorLocation(FVector(newLocation.X,newLocation.Y,newLocation.Z+30));
	startZ = source->GetActorLocation().Z;
}
