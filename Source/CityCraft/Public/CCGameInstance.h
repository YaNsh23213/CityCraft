// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CCGameInstance.generated.h"

UENUM(BlueprintType)
enum class EHexBiome : uint8
{
    Clear UMETA(DisplayName = "Clear"),
    Snow UMETA(DisplayName = "Snow"),
    Desert UMETA(DisplayName = "Desert"),
    Meadow UMETA(DisplayName = "Meadow"),
    Plain UMETA(DisplayName = "Plain"),
    Ocean UMETA(DisplayName = "Ocean"),
    Coast UMETA(DisplayName = "Coast"),
    Lake UMETA(DisplayName = "Lake")
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
    TArray<UStaticMesh*> MeadowHillWoodMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> SnowMeshArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UStaticMesh*> SnowHillMeshArray;
};
UCLASS() class CITYCRAFT_API UCCGameInstance : public UGameInstance
{
    GENERATED_BODY()
};
