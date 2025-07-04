// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCGameInstance.h"
#include "CCBaseHexagonActor.generated.h"

class ACCItemHexagonActor;
class ACCTownHexagonActor;


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

    void SpawnAndReplace(TSubclassOf<ACCItemHexagonActor> ReplaceHexClass, int32 IndexArrayHex, EHexBiome OldBiome);

    TSubclassOf<ACCItemHexagonActor> GetTownClass() const { return TownHexClass; }

    UFUNCTION(BlueprintCallable)
    FMeshData GetMeshData() const { return DataMesh; }

protected:

    UPROPERTY()
    FGenerationConfigStruct CurrentInfo;

    // Base hexagon item
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    TSubclassOf<ACCItemHexagonActor> HexClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    TSubclassOf<ACCItemHexagonActor> TownHexClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    int32 HexDiameterC = 200;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    int32 MaxYC = 10;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    int32 MaxXC = 10;

    // Generator Config

   

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FMeshData DataMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FLakeModuleCorrectionStruct> LakeModuleCorrection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FRiverModuleCorrectionStruct> MainRiverModuleCorrection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FRiverModuleCorrectionStruct> StartRiverModuleCorrection;

private:
    UPROPERTY()
    TArray<ACCItemHexagonActor*> HexArray;

    void MakeRiver(ACCItemHexagonActor* HexCurrent);
    void ModuleRiver(TArray<ACCItemHexagonActor*> RiverHexArray);

    bool CheackValidIndexRiver(int32 CurrentIndex);
    bool CheackValidBiomToRiver(ACCItemHexagonActor* CurrentHex);

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
