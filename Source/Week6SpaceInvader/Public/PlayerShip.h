// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "PlayerShip.generated.h"

UCLASS()
class WEEK6SPACEINVADER_API APlayerShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerMesh")
UStaticMeshComponent* PlayerMesh = nullptr;

UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerMesh")
USpringArmComponent* SpringArm {nullptr};
UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerMesh")
UCameraComponent* Camera = nullptr;

UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerMesh")
float Speed = 5.f;

UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerMesh")
int Ammo = 30;

UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerMesh")
int MaxAmmo = 30;

UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerMesh")
USoundBase* ShootingSound = nullptr;

UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerMesh")
UShapeComponent* CollisionBox =nullptr;

UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerMesh")
USoundBase* ReloadingSound = nullptr;

UPROPERTY(EditAnywhere, meta =(AllowPrivateAccess = "true"));
TSubclassOf<AActor> ActorToSpawn;

UPROPERTY(EditAnywhere, meta =(AllowPrivateAccess = "true"));
TSubclassOf<AActor> ActorEney;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
class UWidgetComponent* AmoUIComp;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
TSubclassOf<UUserWidget> ScreenUiWidget;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
UUserWidget* MainWidgetPtr = nullptr;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
class UWidgetComponent* MainUiComp;

void Reload();

void Shoot();



UFUNCTION(BlueprintCallable)
void ResetLocation() const;


UFUNCTION(BlueprintCallable)
int RetMaxAmo();

UFUNCTION(BlueprintCallable)
int RetAmmo();


bool InContact;

protected: 
	void ResetGame();
	bool bEnemyDied = false;
	void SetDead();
private:
FVector InitLocation = FVector::ZeroVector;


void MoveXAxis(float Value);
void MoveYAxis(float Value);


void Dash();
float XValue = 0.f;
float YValue = 0.f;
float DashTimer = 0.f;


UFUNCTION()
void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
friend class AWeek6SpaceInvaderGameModeBase;

};

