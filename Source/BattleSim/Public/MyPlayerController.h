// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

public:
    // Widget�������
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "UI")
	UUserWidget* PauseMenuInstance;
	void BeginPlay() override;
    TSubclassOf<UUserWidget> PauseMenuClass;
    AMyPlayerController();
};