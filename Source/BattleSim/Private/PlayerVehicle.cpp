

#include "PlayerVehicle.h"

APlayerVehicle::APlayerVehicle() :AVehicle()
{
	//bind mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/PlayerTank.PlayerTank'"));

	float scale = 0.5f;
	MeshComponent->SetRelativeScale3D(FVector(scale,scale,scale));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
	//set widget scale
	float widgetScale = 0.85f;
	infoWidgetComponent->SetRelativeScale3D(FVector(widgetScale / scale, widgetScale / scale, widgetScale / scale));
}

void APlayerVehicle::BeginPlay()
{
	Super::BeginPlay();
	setTextColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
}
