// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerShip.h"
#include "WAmoBar.generated.h"

/**
 * 
 */
UCLASS()
class WEEK6SPACEINVADER_API UWAmoBar : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetOwner(APlayerShip* PlayerShip){
		PlayerShipPtr = PlayerShip;
	}
	TWeakObjectPtr<APlayerShip> PlayerShipPtr;
protected:

UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="UI", meta =(BindWidget))
class UProgressBar* AmoBar;
UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="UI",meta =(BindWidget))
class UTextBlock* AmoNO;
UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="UI",meta =(BindWidget))
class UTextBlock* AmoMax;

public:
void NativeTick(const FGeometry & MyGeometry,float InDeltaTime) override;
	
};
