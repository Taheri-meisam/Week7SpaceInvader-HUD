// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class WEEK6SPACEINVADER_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector MoveDirection = FVector(1.f, 0.f, 0.f);
	void ImHit();
    bool DeleteThisEnemy{false};
private:
    UPROPERTY(EditAnywhere)
    float Speed = -50.f;
    
    UPROPERTY(EditAnywhere)
    float DestroyPlacement = -2000.f;


};
