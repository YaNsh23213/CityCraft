// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCItemHexagonActor.h"
#include "CCTownHexagonActor.generated.h"

/**
 * 
 */
UCLASS()
class CITYCRAFT_API ACCTownHexagonActor : public ACCItemHexagonActor
{
	GENERATED_BODY()
public:

    virtual void InteractionItem() override;

protected:

private:
    UPROPERTY()
    FString OwnerPlayer = "";

    UPROPERTY()
    int32 LevelTown = 1;

    UPROPERTY()
    int32 AmountPeople = 1;
};
