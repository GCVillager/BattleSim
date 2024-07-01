

#include "EnemyVehicle.h"

void AEnemyVehicle::BeginPlay()
{
	Super::BeginPlay();
	setTextColor(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
}

AEnemyVehicle::AEnemyVehicle() :AVehicle()
{
	status = ALIVE;
}

void AEnemyVehicle::setStatus(VehicleStatus newStatus)
{
	status = newStatus;
	if (status == TARGETED)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyVehicle::destroy, 3.0f, false);
	}
	else if (status == DEAD)
	{
		destroy();
	}
}

void AEnemyVehicle::setInfo(std::string info) 
{
	//add * to the text if status == targeted
	if (status == TARGETED )
	{
		info = "*" + info + "*";
		//set color to red
		setTextColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
	}
	AVehicle::setInfo(info);
}

void AEnemyVehicle::destroy()
{
	//set invisible
	SetActorHiddenInGame(true);
}

VehicleStatus AEnemyVehicle::getStatus()
{
	return status;
}