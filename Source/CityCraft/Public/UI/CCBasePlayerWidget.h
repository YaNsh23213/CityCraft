// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CCBasePlayerWidget.generated.h"

class UTextBlock;
class USizeBox;
class UImage;

UCLASS()
class CITYCRAFT_API UCCBasePlayerWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void ChangeHex();

    void UpdateMainInfo(UTexture2D* IMage, FText Name, FText IsFreeStatus);
    void UpdateStatusEat(bool Value, int32 Amount);
    void UpdateStatusProduction(bool Value, int32 Amount);
    void UpdateStatusGold(bool Value, int32 Amount);
    void UpdateStatusEatStorage(bool Value, int32 Amount);
    void UpdateStatusProductionStorage(bool Value, int32 Amount);
    void UpdateStatusGoldStorage(bool Value, int32 Amount);

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* EatText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ProductionText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* GoldText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* EatStorageText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ProductionStorageText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* GoldStorageText;

    // SizeBox

    UPROPERTY(meta = (BindWidget))
    USizeBox* EatBox;

    UPROPERTY(meta = (BindWidget))
    USizeBox* ProductionBox;

    UPROPERTY(meta = (BindWidget))
    USizeBox* GoldBox;

    UPROPERTY(meta = (BindWidget))
    USizeBox* EatStorageBox;

    UPROPERTY(meta = (BindWidget))
    USizeBox* ProductionStorageBox;

    UPROPERTY(meta = (BindWidget))
    USizeBox* GoldStorageBox;

    UPROPERTY(meta = (BindWidget))
    USizeBox* MainInfoBox;

    // MainHexInfo

    UPROPERTY(meta = (BindWidget))
    UTextBlock* NameBiome;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* IsFreeBiome;

    UPROPERTY(meta = (BindWidget))
    UImage* ImageBiome;

private:
    void UpdateStatus(USizeBox* Box, UTextBlock* Block, int32 Amount, bool Value);
};
