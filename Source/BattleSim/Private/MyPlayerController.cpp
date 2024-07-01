// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"

AMyPlayerController::AMyPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP_PauseUI.BP_PauseUI_C'"));
	if (WidgetClassFinder.Succeeded())
	{
		PauseMenuClass = WidgetClassFinder.Class;
	}
}
void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 绑定键盘事件
	InputComponent->BindAction("Escape", IE_Pressed, this, &AMyPlayerController::OnEscapePressed);
	InputComponent->BindAction("Focus", IE_Pressed, this, &AMyPlayerController::OnFocusPressed);
}

void AMyPlayerController::OnEscapePressed()
{
	//创建Widget
	if (PauseMenuClass)
	{
		PauseMenuInstance = CreateWidget<UUserWidget>(this, PauseMenuClass);
		if (PauseMenuInstance)
		{
			PauseMenuInstance->AddToViewport();
		}
	}
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	SetPause(true);
}

void AMyPlayerController::BeginPlay()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

PRAGMA_DISABLE_OPTIMIZATION

void AMyPlayerController::OnFocusPressed()
{
	//get pawn
	APawn* MyPawn = GetPawn();
	TArray<AActor*> playerVehicles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerVehicle::StaticClass(), playerVehicles);
	APlayerVehicle* player = Cast<APlayerVehicle>(playerVehicles[0]);
	FVector vehiclePos = player->GetActorLocation();
	FRotator vehicleRot = player->GetActorRotation();
	const float distance = 1000.0f;
	float yaw =  vehicleRot.Yaw;
	float dx = distance * FMath::Cos(FMath::DegreesToRadians(yaw));
	float dy = distance * FMath::Sin(FMath::DegreesToRadians(yaw));
	FVector newLocation = vehiclePos + FVector(-dx, -dy, 500);
	MyPawn->SetActorLocation(newLocation);
	AMyPlayerController* controller = Cast<AMyPlayerController>(MyPawn->GetController());
	if (controller)
	{
		controller->SetControlRotation(FRotator(FMath::RadiansToDegrees(FMath::Tan(-50.0 / 100.0)), yaw, 0));
		//set location
	}
	//MyPawn->SetActorRotation(FRotator(FMath::Tan(-50.0 / 100.0), -yaw, 0));
}

PRAGMA_ENABLE_OPTIMIZATION