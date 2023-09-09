// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCBaseHexagonActor.generated.h"

class ACCItemHexagonActor;

UCLASS()
class CITYCRAFT_API ACCBaseHexagonActor : public AActor
{
    GENERATED_BODY()

public:
    ACCBaseHexagonActor();

    virtual void Tick(float DeltaTime) override;

    void InitMap(int32 HexDiameter, int32 MaxY, int32 MaxX);

protected:
    // Base hexagon item
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    TSubclassOf<ACCItemHexagonActor> HexClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    int32 HexDiameterC = 200;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    int32 MaxYC = 10;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    int32 MaxXC = 10;

    virtual void BeginPlay() override;

private:
};
