// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CCBasePlayerWidget.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UCCBasePlayerWidget::ChangeHex()
{
    UpdateStatus(EatBox, EatText, 0, false);
    UpdateStatus(ProductionBox, ProductionText, 0, false);
    UpdateStatus(GoldBox, GoldText, 0, false);
    UpdateStatus(EatStorageBox, EatStorageText, 0, false);
    UpdateStatus(ProductionStorageBox, ProductionStorageText, 0, false);
    UpdateStatus(GoldStorageBox, GoldStorageText, 0, false);
}

void UCCBasePlayerWidget::UpdateMainInfo(UTexture2D* IMage, FText Name, FText IsFreeStatus)
{
    if (IMage)
    {
        ImageBiome->SetBrushFromTexture(IMage);
    }
    NameBiome->SetText(Name);
    IsFreeBiome->SetText(IsFreeStatus);
}

void UCCBasePlayerWidget::UpdateStatusEat(bool Value, int32 Amount)
{
    UpdateStatus(EatBox, EatText, Amount, Value);
}

void UCCBasePlayerWidget::UpdateStatusProduction(bool Value, int32 Amount)
{
    UpdateStatus(ProductionBox, ProductionText, Amount, Value);
}

void UCCBasePlayerWidget::UpdateStatusGold(bool Value, int32 Amount)
{
    UpdateStatus(GoldBox, GoldText, Amount, Value);
}

void UCCBasePlayerWidget::UpdateStatusEatStorage(bool Value, int32 Amount)
{
    UpdateStatus(EatStorageBox, EatStorageText, Amount, Value);
}

void UCCBasePlayerWidget::UpdateStatusProductionStorage(bool Value, int32 Amount)
{
    UpdateStatus(ProductionStorageBox, ProductionStorageText, Amount, Value);
}

void UCCBasePlayerWidget::UpdateStatusGoldStorage(bool Value, int32 Amount)
{
    UpdateStatus(GoldStorageBox, GoldStorageText, Amount, Value);
}

void UCCBasePlayerWidget::UpdateStatus(USizeBox* Box, UTextBlock* Block, int32 Amount, bool Value)
{
    Value ? Box->SetVisibility(ESlateVisibility::Visible) : Box->SetVisibility(ESlateVisibility::Hidden);
    Block->SetText(FText::FromString(FString::FromInt(Amount)));
}
