// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CCGameInstance.generated.h"

class ACCItemHexagonActor;

UENUM(BlueprintType)
enum class EHexBiome : uint8
{
    Clear UMETA(DisplayName = "Clear"),
    Snow UMETA(DisplayName = "Snow"),
    Desert UMETA(DisplayName = "Desert"),
    Meadow UMETA(DisplayName = "Meadow"),
    Ocean UMETA(DisplayName = "Ocean"),
    Coast UMETA(DisplayName = "Coast"),
    River UMETA(DisplayName = "River"),
    Lake UMETA(DisplayName = "Lake"),
    SnowHill UMETA(DisplayName = "SnowHill"),
    DesertHill UMETA(DisplayName = "DesertHill"),
    MeadowHill UMETA(DisplayName = "MeadowHill"),
    SnowHillWood UMETA(DisplayName = "SnowHillWood"),
    DesertHillWood UMETA(DisplayName = "DesertHillWood"),
    MeadowHillWood UMETA(DisplayName = "MeadowHillWood"),
    SnowWood UMETA(DisplayName = "SnowWood"),
    DesertWood UMETA(DisplayName = "DesertWood"),
    MeadowWood UMETA(DisplayName = "MeadowWood")
};
USTRUCT(BlueprintType)
struct FMeshData
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> DesertMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> DesertHillMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> MeadowMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> MeadowHillMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> MeadowWoodMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> DesertWoodMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> SnowWoodMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> MeadowHillWoodMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> DesertHillWoodMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> SnowHillWoodMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> SnowMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> SnowHillMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> LakeMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> RiverMeshArray;
};
USTRUCT(BlueprintType)
struct FRadiusReturnHexStruct
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ACCItemHexagonActor* HexRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 IndexRadiusHex;
};
USTRUCT(BlueprintType)
struct FLakeModuleCorrectionStruct
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> ArrayLandIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* LakeMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RotationCorrection = 30;
};
USTRUCT(BlueprintType)
struct FRiverModuleCorrectionStruct
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> ArrayRiverIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> RiverMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RotationCorrection = 30;
};
USTRUCT(BlueprintType)
struct FStorageStruct
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 EatStorage = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ProductionStorage = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GoldStorage = 0;
};
USTRUCT(BlueprintType)
struct FProductivityStruct
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 EatProductivity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ProductionProductivity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GoldProductivity;
};
USTRUCT(BlueprintType)
struct FBuildMeshData
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSoftObjectPtr<UStaticMesh>> SDesertBuildArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSoftObjectPtr<UStaticMesh>> MDesertBuildArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSoftObjectPtr<UStaticMesh>> BDesertBuildArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSoftObjectPtr<UStaticMesh>> SSnowBuildArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSoftObjectPtr<UStaticMesh>> MSnowBuildArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSoftObjectPtr<UStaticMesh>> BSnowBuildArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSoftObjectPtr<UStaticMesh>> SMeadowBuildArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSoftObjectPtr<UStaticMesh>> MMeadowBuildArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSoftObjectPtr<UStaticMesh>> BMeadowBuildArray;
};

USTRUCT(BlueprintType)
struct FGenerationConfigStruct
{
    GENERATED_USTRUCT_BODY()

public:
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

    // RiverSettings

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0, ClampMax = 100))
    int32 AmountRiver = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0, ClampMax = 100))
    int32 MinLengthRiver = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeneratorConfig", meta = (ClampMin = 0, ClampMax = 100))
    int32 MaxLengthRiver = 2;

    //
};

UCLASS() class CITYCRAFT_API UCCGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FBuildMeshData GetBuildMeshData() const { return BuildMeshData; }

    UFUNCTION(BlueprintCallable)
    void SetGenerationConfig(FGenerationConfigStruct Data) { GenerationMapConfig = Data; }

    FGenerationConfigStruct GetFGenerationConfigStruct(){ return GenerationMapConfig; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FBuildMeshData BuildMeshData;

    UPROPERTY()
    FGenerationConfigStruct GenerationMapConfig;

private:
};
