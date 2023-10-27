// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCGameInstance.h"
#include "CCBaseHexagonActor.generated.h"

class ACCItemHexagonActor;

UCLASS()
class CITYCRAFT_API ACCBaseHexagonActor : public AActor
{
    GENERATED_BODY()

public:
    ACCBaseHexagonActor();

    virtual void Tick(float DeltaTime) override;
    virtual void OnConstruction(const FTransform& Transform) override;

    UFUNCTION(BlueprintCallable)
    void InitMap(int32 HexDiameter, int32 MaxY, int32 MaxX);
    void StartGenerate();

    TArray<ACCItemHexagonActor*> GetHexArray() const { return HexArray; }

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

    // Generator Config

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float PercentSnow = 0.33;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float PercentSnowOverlap = 0.1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float PercentDesert = 0.33;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig")
    float PercentDesertOverlap = 0.1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 1))
    int32 MinOverlapAmount = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 150))
    int32 MaxOverlapAmount = 200;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float SnowHilFrequency = 0.5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float MeadowHilFrequency = 0.5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float DesertHilFrequency = 0.5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float MeadowWoodFrequency = 0.5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float SnowWoodFrequency = 0.5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float DesertWoodFrequency = 0.5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0, ClampMax = 100))
    int32 AmountLake = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float StartedChanceUpLake = 0.5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    float StepChanceDownLake = 0.5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
    bool NeedGenerateModuleLake = true;

    // Watter settings
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0))
    bool HaveOcean = true;

    UPROPERTY(
        EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0, EditCondition = "HaveOcean == true"))
    bool ContinentTwo = false;

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    FMeshData GetMeshData() const { return DataMesh; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FMeshData DataMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FLakeModuleCorrectionStruct> LakeModuleCorrection;

private:
    UPROPERTY()
    TArray<ACCItemHexagonActor*> HexArray;

    int32 FindMinMax(bool IsX, bool IsMax);

    ACCItemHexagonActor* GetHexFromIdex(FVector2D Position);

    TArray<FRadiusReturnHexStruct> GetFirstRadiusHex(ACCItemHexagonActor* BaseHex);
    TArray<FRadiusReturnHexStruct> GetSecondRadiusHex(ACCItemHexagonActor* BaseHex);
    TArray<FRadiusReturnHexStruct> GetThirdRadiusHex(ACCItemHexagonActor* BaseHex);

    bool IsEqual(TArray<int32> Array1, TArray<int32> Array2);

    TArray<FVector2D> FirstRadiusModifier = {{0, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, 0}, {-1, 1}};
    TArray<FVector2D> SecondRadiusModifier = {
        {0, 2}, {1, 1}, {2, 0}, {2, -1}, {2, -2}, {1, -2}, {0, -2}, {-1, -1}, {-2, 0}, {-2, 1}, {-2, 2}, {-1, 2}};
    TArray<FVector2D> ThirdRadiusModifier = {{0, 3}, {1, 2}, {2, 1}, {3, 0}, {3, -1}, {3, -2}, {3, -3}, {2, -3}, {1, -3}, {0, -3}, {-1, -2},
        {-2, -1}, {-3, 0}, {-3, 1}, {-3, 2}, {-3, 3}, {-2, 3}, {-1, 3}};
};
