// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerVehicle.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESIM_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
    virtual void SetupInputComponent() override;

    // ���崦���ض������¼��ĺ���
    void OnEscapePressed();
    void OnFocusPressed();
	void OnGlobalPressed();
public:
    // Widget�������
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "UI")
	UUserWidget* PauseMenuInstance;
    TSubclassOf<UUserWidget> PauseMenuClass;

	void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
    TSubclassOf<UUserWidget> HUDWidgetClass;
    UUserWidget* HUDWidget;

    void changeTip(FString appendText);

    AMyPlayerController();
};
