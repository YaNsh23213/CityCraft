// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCBaseUnitActor.generated.h"

UCLASS()
class CITYCRAFT_API ACCBaseUnitActor : public AActor
{
    GENERATED_BODY()

public:
    ACCBaseUnitActor();

    virtual void Tick(float DeltaTime) override;

    FString GetTeam() const { return Team; }

protected:

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    FString Team;
};
