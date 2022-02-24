// Fill out your copyright notice in the Description page of Project Settings.


#include "WAmoBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Math/Color.h"



void UWAmoBar::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if(PlayerShipPtr.IsValid()){
        float RemainingAmmo =(float) PlayerShipPtr->RetAmmo();
        float BarPercent = float(RemainingAmmo /(float)PlayerShipPtr->RetMaxAmo());
        if (RemainingAmmo < 15.f && RemainingAmmo > 10.f ){
            AmoBar->SetFillColorAndOpacity(FLinearColor(50.f, 20.f, 0.f));
        }
        if (RemainingAmmo < 5.f) {
            AmoBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
        }
        if (RemainingAmmo > 15.f && RemainingAmmo <= 30.f) {
            AmoBar->SetFillColorAndOpacity(FLinearColor(0.f, 0.49f, 1.f));
        }

        AmoBar->SetPercent(BarPercent);
        AmoNO->SetText(FText::AsNumber(PlayerShipPtr->RetAmmo()));

    }else{
        return;
    }

}

