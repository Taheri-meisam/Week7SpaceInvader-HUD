// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUIwidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Math/Color.h"

void UMainUIwidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);



    if (PlayerShipPtrs){
        float RemainingAmmo = (float)PlayerShipPtrs->RetAmmo();
        float BarPercent = float(RemainingAmmo / (float)PlayerShipPtrs->RetMaxAmo());
        if (RemainingAmmo < 15.f && RemainingAmmo > 10.f) {
            AmoBar->SetFillColorAndOpacity(FLinearColor(50.f, 20.f, 0.f));
        }
        if (RemainingAmmo < 5.f) {
            AmoBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
        }
        if (RemainingAmmo > 15.f && RemainingAmmo <= 30.f) {
            AmoBar->SetFillColorAndOpacity(FLinearColor(0.f, 0.49f, 1.f));
        }

        AmoBar->SetPercent(BarPercent);
        AmoNO->SetText(FText::AsNumber(PlayerShipPtrs->RetAmmo()));

    }
    else {
        return;
    }


    if (GameModePtrs) {
        float RemainingEnemy = (int)GameModePtrs->RetNoEnemy();
        float EnemyBarPercent = (float)(RemainingEnemy / (float)GameModePtrs->MaxEnemy);
        EnemyBar->SetPercent(EnemyBarPercent);
        EnemyMax->SetText(FText::AsNumber(GameModePtrs->MaxEnemy));
        EnemyNO->SetText(FText::AsNumber(GameModePtrs->RetNoEnemy()));
    }
    else {
        return;
    }


}
