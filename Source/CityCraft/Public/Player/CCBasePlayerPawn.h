// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CCGameInstance.h"
#include "CCBasePlayerPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCCBasePlayerWidget;

UCLASS()
class CITYCRAFT_API ACCBasePlayerPawn : public APawn
{
    GENERATED_BODY()

public:
    ACCBasePlayerPawn();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void SetSensitive(float Value) { Sensitive = Value; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    // UI

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UCCBasePlayerWidget> BasePlayerWidgetClass;

    UPROPERTY()
    ACCItemHexagonActor* CurrentSelected;

private:
    UFUNCTION()
    void MoveUpDown(float Value);

    UFUNCTION()
    void MoveLeftRight(float Value);

    UFUNCTION()
    void LeftMouseClick();

    FText GetEnumAsString(EHexBiome EnumValue);

    UPROPERTY()
    float Sensitive = 15.0f;

    // UI

    UPROPERTY()
    UCCBasePlayerWidget* BasePlayerWidget;

    void UpdateWidgetInfoFromHexInfo(FStorageStruct DataS, FProductivityStruct DataP, FText NameHex, FText IsFree, UTexture2D* NewImage);
};
