// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"

AMyPlayerController::AMyPlayerController()
{
	//init ESC menu
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP_PauseUI.BP_PauseUI_C'"));
	if (WidgetClassFinder.Succeeded())
	{
		PauseMenuClass = WidgetClassFinder.Class;
	}

	//init HUD
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder2(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP_HUDTips.BP_HUDTips_C'"));
	if (WidgetClassFinder2.Succeeded())
	{
		HUDWidgetClass = WidgetClassFinder2.Class;
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
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	//create HUD
	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		//change text
		FString text = TEXT("按下ESC以暂停游戏，可在此页面重新开始、继续或退出\n敌方单位头顶信息分别为威胁等级和威胁分数\nWASD移动，空格上升，CTRL下降\n按下F以追踪我方单位");
		UTextBlock* textBlock = Cast<UTextBlock>(HUDWidget->GetWidgetFromName("TextBlock_Tips"));
		if (textBlock)
		{
			textBlock->SetText(FText::FromString(text));
		}
		
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void AMyPlayerController::OnFocusPressed()
{
	//get pawn
	APawn* MyPawn = GetPawn();
	TArray<AActor*> playerVehicles;
	//get the player vehicle
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerVehicle::StaticClass(), playerVehicles);
	APlayerVehicle* player = Cast<APlayerVehicle>(playerVehicles[0]);
	FVector vehiclePos = player->GetActorLocation();
	FRotator vehicleRot = player->GetActorRotation();
	
	//calculate the new location of Pawn
	const float distance = 1000.0f;
	float yaw =  vehicleRot.Yaw;
	float dx = distance * FMath::Cos(FMath::DegreesToRadians(yaw));
	float dy = distance * FMath::Sin(FMath::DegreesToRadians(yaw));
	FVector newLocation = vehiclePos + FVector(-dx, -dy, 500);

	//set location and rotation
	MyPawn->SetActorLocation(newLocation);
	AMyPlayerController* controller = Cast<AMyPlayerController>(MyPawn->GetController());
	if (controller)
	{
		controller->SetControlRotation(FRotator(FMath::RadiansToDegrees(FMath::Tan(-50.0 / 100.0)), yaw, 0));
	}
	//MyPawn->SetActorRotation(FRotator(FMath::Tan(-50.0 / 100.0), -yaw, 0));
}
