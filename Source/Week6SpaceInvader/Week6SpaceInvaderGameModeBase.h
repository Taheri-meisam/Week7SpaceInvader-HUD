// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy.h"
#include "PlayerShip.h"
#include "Week6SpaceInvaderGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WEEK6SPACEINVADER_API AWeek6SpaceInvaderGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
    AWeek6SpaceInvaderGameModeBase();


    virtual void BeginPlay() override;

   
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Variables")
    int ArraySize = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Variables")
    bool bAllDead = false;

    UFUNCTION(BlueprintCallable)
    bool ReturnDead();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Variables")
    int MaxEnemy = 0;
    int RetNoEnemy();

private:
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<class AEnemy> EnemyBP;

    UPROPERTY(EditAnywhere, Category = "Spawning")
    float SpawnDelay = 2.f ;

    float EnemyTimer = 0.f ;

    float EnemyTurnTime = 0.f ;

    int EnemyMoveDirection = 1 ;

    TArray<class AEnemy*> EnemyArray;
   
	
};
