// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CCMainGameMode.generated.h"

class ACCBaseHexagonActor;
class ACCBasePlayerController;

UCLASS()
class CITYCRAFT_API ACCMainGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    void AfterGeneration(ACCBaseHexagonActor* GenetationActor);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<ACCBaseHexagonActor> GenerationActorClass;

private:
    UPROPERTY()
    TArray<ACCBasePlayerController*> PlayerContollerArray;
};
