


#include "BattleSimGameModeBase.h"

ABattleSimGameModeBase::ABattleSimGameModeBase()
{
	gameController = new UEController();
	PrimaryActorTick.bCanEverTick = true;
	//set player controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Script/Engine.Blueprint'/Game/BP_PlayerController.BP_PlayerController_C'"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
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