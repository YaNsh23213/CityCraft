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
    Meadow UMETA(DisplayName = "Meadow")
};
UCLASS()
class CITYCRAFT_API UCCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
};
