// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CCBasePlayerController.generated.h"

class ACCBasePlayerPawn;

UCLASS()
class CITYCRAFT_API ACCBasePlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    void InitPawn(FVector Location);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<ACCBasePlayerPawn> PlayerPawnClass;
};
