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

void AMyPlayerController::OnFocusPressed()
{

}