// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCItemHexagonActor.h"
#include "CCTownHexagonActor.generated.h"

class ACCBasePlayerPawn;
class ACCSpawnPointBuildActor;

UCLASS()
class CITYCRAFT_API ACCTownHexagonActor : public ACCItemHexagonActor
{
    GENERATED_BODY()
public:
    ACCTownHexagonActor();

    virtual void InteractionItem(ACCBasePlayerPawn* ActorOwner) override;
    virtual void InitHex() override;
    virtual void InitBuildSet();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
    TSubclassOf<ACCSpawnPointBuildActor> SpawnPointBuildActorClass;

private:
    TArray<ACCSpawnPointBuildActor*> ResetAllSpawnPoint();

    UPROPERTY()
    TArray<ACCSpawnPointBuildActor*> SpawnPointArray;

    UPROPERTY()
    FString OwnerPlayer = "";

    UPROPERTY()
    int32 LevelTown = 1;

    UPROPERTY()
    int32 AmountPeople = 1;

    //GenerateLevelsTown
    void GenerateBaseSnowTown();
    void GenerateBaseDesertTown();
    void GenerateBaseMeadowTown();


};
