// Copyright Epic Games, Inc. All Rights Reserved.


#include "Week6SpaceInvaderGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AWeek6SpaceInvaderGameModeBase::AWeek6SpaceInvaderGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
    bAllDead = false;

}

void AWeek6SpaceInvaderGameModeBase::BeginPlay()
{ 
    bAllDead = false;
    UWorld* World = GetWorld();
    if (World)
    {
        for (int j{ 1 }; j < 5; j++)
        {
            for (int i{ 1 }; i < 11; i++)
            {
                FVector Location = FVector((800.f - j * 200), (-1000.f + i * 200), 70.f);
                AEnemy* tempEnemy = World->SpawnActor<AEnemy>(EnemyBP, Location, FRotator::ZeroRotator);
                EnemyArray.Add(tempEnemy);
                ArraySize++;
            }
        }
       // UE_LOG(LogTemp, Error, TEXT("Enemy Array is: %d "), EnemyArray.Num());
    }
    MaxEnemy = ArraySize;
}

void AWeek6SpaceInvaderGameModeBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    EnemyTimer += DeltaSeconds;
    EnemyTurnTime += DeltaSeconds;
    if (EnemyTurnTime > 4.0f)
    {
       // UE_LOG(LogTemp, Error, TEXT("Enemy Move Logic Running"));
        for (int i = 0; i < EnemyArray.Num(); i++)
        {
            if (EnemyArray[i]->DeleteThisEnemy) {
                EnemyArray[i]->Destroy();
                EnemyArray.RemoveAt(i);
               // UE_LOG(LogTemp, Error, TEXT("Enemy down. Enemy Array is: %d "), EnemyArray.Num());
                ArraySize--;
                }
            
        }
        for (auto Enemy : EnemyArray) //for (int i = 0; i < EnemyArray.Num(); i++)
        {
            switch (EnemyMoveDirection) {
            case 1:
                Enemy->MoveDirection = FVector(1.0f, 0.f, 0.f);
                break;
            case 2:
                Enemy->MoveDirection = FVector(0.0f, 1.f, 0.f);
                break;
            case 3:
                Enemy->MoveDirection = FVector(1.0f, 0.f, 0.f);
                break;
            case 4:
                Enemy->MoveDirection = FVector(0.0f, -1.f, 0.f);
                break;
            default:
               // UE_LOG(LogTemp, Error, TEXT("Enemy Move Logic not working!"));
                break;
            }
        }
        EnemyMoveDirection = ((EnemyMoveDirection) % 4) + 1;
        //EnemyMoveDirection = FMath::FloorToInt(FMath::FRandRange(1.f,4.f));
        EnemyTurnTime = 0.f;
    }

}

bool AWeek6SpaceInvaderGameModeBase::ReturnDead()
{
    if (ArraySize == 0) {
        bAllDead = true;
        return bAllDead;
    }
    return false;
}


int AWeek6SpaceInvaderGameModeBase::RetNoEnemy(){
    return ArraySize;
}