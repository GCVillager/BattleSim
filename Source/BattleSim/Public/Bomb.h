// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerVehicle.h"
#include "EnemyVehicle.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Bomb.generated.h"

UCLASS()
class BATTLESIM_API ABomb : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//mesh
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BombMesh;

	//material
	UPROPERTY(VisibleAnywhere)
	UMaterialInterface* Material;

	APlayerVehicle* source;
	AEnemyVehicle* destination;
	const float timeToExplode = 3.0f;
	float startZ;
	float velocityZ;
	float totalTime=0;
	float upTime;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void init(APlayerVehicle* Source ,AEnemyVehicle* Destination);
};
