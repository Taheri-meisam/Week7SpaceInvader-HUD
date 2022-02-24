// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Math/Color.h"

void UClassHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);



    if (PlayerShipPtr2) {
        float RemainingAmmo = (float)PlayerShipPtr2->RetAmmo();
        float BarPercent = float(RemainingAmmo / (float)PlayerShipPtr2->RetMaxAmo());
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
        AmoNO->SetText(FText::AsNumber(PlayerShipPtr2->RetAmmo()));

    }
    else {
        return;
    }


    if (GameModePtr2) {
        float RemainingEnemy = (int)GameModePtr2->RetNoEnemy();
        float EnemyBarPercent = (float)(RemainingEnemy / (float)GameModePtr2->MaxEnemy);
        EnemyBar->SetPercent(EnemyBarPercent);
        EnemyMax->SetText(FText::AsNumber(GameModePtr2->MaxEnemy));
        EnemyNO->SetText(FText::AsNumber(GameModePtr2->RetNoEnemy()));
    }
    else {
        return;
    }
}
