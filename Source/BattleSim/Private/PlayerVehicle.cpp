

#include "PlayerVehicle.h"

APlayerVehicle::APlayerVehicle() :AVehicle()
{
	//bind mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/PlayerTank.PlayerTank'"));

	MeshComponent->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}

void APlayerVehicle::BeginPlay()
{
	Super::BeginPlay();
	setTextColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
}
