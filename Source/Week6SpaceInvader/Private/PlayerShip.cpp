#include "PlayerShip.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"
#include "bullet.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "Engine/Engine.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "WAmoBar.h"
#include "Engine/World.h"
#include  <MainUIwidget.h>


// Sets default values
APlayerShip::APlayerShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	SetRootComponent(PlayerMesh);
	SpringArm =  CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);

	SpringArm->SetRelativeRotation(FRotator(-30.f,0.f,0.f));
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;
	
	SpringArm->SetupAttachment(PlayerMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Model3D(TEXT("StaticMesh'/Game/Assets/Models/Ships/SciFi_Fighter.SciFi_Fighter'"));

	if (Model3D.Succeeded()) {
		PlayerMesh->SetStaticMesh(Model3D.Object);
	}
//	PlayerMesh->SetSimulatePhysics(true);
	AmoUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("AmoBar"));
	AmoUIComp->SetupAttachment(PlayerMesh);
	MainUiComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("MainWidgetPtr"));

}



static void InitializeDefaultPawnInputBinding()
{
static bool bindingsAdded = false;

if(bindingsAdded == false)
{
	bindingsAdded = true;

	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveX",EKeys::W,1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveX",EKeys::S,-1.f));

	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveY",EKeys::D,1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveY",EKeys::A,-1.f));

	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Shoot",EKeys::SpaceBar));
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Reload",EKeys::R));
	//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Restart", EKeys::O));

}

}

// Called when the game starts or when spawned
void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	InitLocation = PlayerMesh->GetComponentLocation();
	CollisionBox = this->FindComponentByClass<UBoxComponent>();
    
    if (CollisionBox)
    {
        CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerShip::OnOverlap);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
    }

	UWAmoBar* AmmoBar = Cast <UWAmoBar>(AmoUIComp->GetUserWidgetObject());
	AmmoBar->SetOwner(this);


	if (ScreenUiWidget) {
		MainWidgetPtr = CreateWidget<UUserWidget>(AActor::GetWorld(), ScreenUiWidget);
	}

	MainWidgetPtr->AddToViewport();
	MainWidgetPtr->SetVisibility(ESlateVisibility::Visible);


}

// Called every frame
void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InContact = false;
	PlayerMesh->AddRelativeLocation(FVector(XValue,YValue,0.f)*Speed);

}

// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent !=nullptr);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InitializeDefaultPawnInputBinding();
	PlayerInputComponent->BindAxis("MoveX",this,&APlayerShip::MoveXAxis);
	PlayerInputComponent->BindAxis("MoveY",this,&APlayerShip::MoveYAxis);
	PlayerInputComponent->BindAction("Shoot",EInputEvent::IE_Pressed,this,&APlayerShip::Shoot);
	PlayerInputComponent->BindAction("MouseLeft",EInputEvent::IE_Pressed,this,&APlayerShip::Shoot);
	
	PlayerInputComponent->BindAction("Reload",EInputEvent::IE_Pressed,this,&APlayerShip::Reload);
	PlayerInputComponent->BindAction("MouseRight",EInputEvent::IE_Pressed,this,&APlayerShip::Reload);
	PlayerInputComponent->BindAction("Restart", EInputEvent::IE_Pressed, this, &APlayerShip::ResetGame);
}

void APlayerShip::ResetLocation() const{

}



void APlayerShip::Shoot(){
	if(Ammo > 0){
		Ammo--;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ammo : !"), FString::FromInt(Ammo)); 
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::Printf(TEXT("Ammo :  %d "), Ammo));


		UWorld* World = GetWorld();
		if(World)
		{
			FVector Location = GetActorLocation();
			//150cm ahead of actor the bullet will be spawn 
			World->SpawnActor<AActor>(ActorToSpawn, Location+FVector(250.f, 0.f, 0.f),GetActorRotation());
			UGameplayStatics::PlaySound2D(World,ShootingSound,1.f,1.f,0.f,0);

		}
		if(Ammo == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("No ammo Reload %d "), Ammo));

		}
	}



	UE_LOG(LogTemp,Warning,TEXT("Shooting"));

}

void APlayerShip::Reload(){
	Ammo = 30;
	UWorld* NewWorld = GetWorld();
	UGameplayStatics::PlaySound2D(NewWorld,ReloadingSound,1.f,1.f,0.f,0);
	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("Reloaded %d "), Ammo));
}


void APlayerShip::MoveXAxis(float Value){
	XValue = Value; 

}
void APlayerShip::MoveYAxis(float Value){
	YValue = Value;
}

void APlayerShip::SetDead()
{
	bEnemyDied = true;
}

void APlayerShip::Dash(){


}
void APlayerShip::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
 if(OtherActor->IsA(AEnemy::StaticClass()))
    {
		UE_LOG(LogTemp,Warning,TEXT("Ship Hit Enemey"));
        bEnemyDied = true;
        this->SetActorHiddenInGame(true);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
    }
	
}

void APlayerShip::ResetGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Reset level"));
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
    if (bEnemyDied)
    {
        UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()),false);
    }
}


int APlayerShip::RetMaxAmo(){
	return MaxAmmo;
}

int APlayerShip::RetAmmo(){
	return Ammo;
}