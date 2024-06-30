


#include "BattleSimGameModeBase.h"

ABattleSimGameModeBase::ABattleSimGameModeBase()
{
	gameController = new UEController();
	PrimaryActorTick.bCanEverTick = true;
	//set player controller
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void ABattleSimGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	gameController->setWorld(GetWorld());
	gameController->BeginPlay();
}

void ABattleSimGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//update controller
	gameController->Tick(DeltaTime);
}

ABattleSimGameModeBase::~ABattleSimGameModeBase()
{
	delete gameController;
}