

#include "Vehicle.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	//disable collision
	SetActorEnableCollision(false);

	//set up info widget
	infoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	infoWidgetComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP_InfoWidget.BP_InfoWidget_C'"));
	if (WidgetClass.Succeeded())
	{
		infoWidgetComponent->SetWidgetClass(WidgetClass.Class);
		infoWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	}
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVehicle::setLocation(FVector location, FRotator rotation)
{
	// Set the location and rotation of the vehicle.
	SetActorLocation(location);
	SetActorRotation(rotation);
}

void AVehicle::updateWidget()
{
	/*!! Should be called every tick!! Let the widget face to the camera.
	 */
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FVector WidgetLocation = infoWidgetComponent->GetComponentLocation();

		// 计算新的朝向，使Widget面向摄像机
		FRotator NewRotation = (CameraLocation - WidgetLocation).Rotation();
		infoWidgetComponent->SetWorldRotation(NewRotation);

	}
}

void AVehicle::setTextColor(FLinearColor color)
{
	// Set the color of the text in the widget.
	if (infoWidgetComponent && infoWidgetComponent->GetWidget())
	{
		//get the text block
		UUserWidget* userWidget = infoWidgetComponent->GetUserWidgetObject();
		UTextBlock* textBlock = Cast<UTextBlock>(userWidget->GetWidgetFromName(FName("TextBlock_EnemyInfo")));
		if (textBlock)
		{
			textBlock->SetColorAndOpacity(color);
		}
	}
}

void AVehicle::setInfo(std::string info)
{
	// Set the text of the widget.
	UTextBlock* textBlock = Cast<UTextBlock>(infoWidgetComponent->GetUserWidgetObject()->GetWidgetFromName(FName("TextBlock_EnemyInfo")));
	if (textBlock)
	{
		FText text = FText::FromString(FString(info.c_str()));
		textBlock->SetText(text);
	}
}