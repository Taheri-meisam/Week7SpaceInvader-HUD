// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerShip.h"
#include "Week6SpaceInvaderClasses.h"
#include "Kismet/GamePlayStatics.h"
#include "../Week6SpaceInvaderGameModeBase.h"
#include "MainUIwidget.generated.h"

/**
 * 
 */
UCLASS()
class WEEK6SPACEINVADER_API UMainUIwidget : public UUserWidget
{
	GENERATED_BODY()
public:
	

	APlayerShip* PlayerShipPtrs = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	//AWeek6SpaceInvaderGameModeBase* GameModePtrs = GetWorld()->GetAuthGameMode<AWeek6SpaceInvaderGameModeBase>();
	AWeek6SpaceInvaderGameModeBase* GameModePtrs = Cast<AWeek6SpaceInvaderGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));



protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UProgressBar* AmoBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UTextBlock* AmoNO;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UTextBlock* AmoMax;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UProgressBar* EnemyBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UTextBlock* EnemyNO;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UTextBlock* EnemyMax;

public:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
