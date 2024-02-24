// Fill out your copyright notice in the Description page of Project Settings.

#include "CCTownHexagonActor.h"
#include "CCBaseHexagonActor.h"
#include "Player/CCBasePlayerPawn.h"
#include "Components/ChildActorComponent.h"
#include "Build/CCSpawnPointBuildActor.h"

ACCTownHexagonActor::ACCTownHexagonActor() {}

void ACCTownHexagonActor::InteractionItem(ACCBasePlayerPawn* ActorOwner)
{
    Super::InteractionItem(ActorOwner);
    UE_LOG(LogTemp, Warning, TEXT("TOWN interaction"))
}

void ACCTownHexagonActor::InitHex()
{
    InitBuildSet();
}

void ACCTownHexagonActor::InitBuildSet()
{
    UE_LOG(LogTemp, Warning, TEXT("InitBuildSet %s"), *GetNameBiome().ToString());
    EHexBiome TempBiome = GetHexBiome();
    if (TempBiome == EHexBiome::Snow || TempBiome == EHexBiome::SnowHill || TempBiome == EHexBiome::SnowHillWood ||
        TempBiome == EHexBiome::SnowWood)
    {
        UE_LOG(LogTemp, Warning, TEXT("GenerateBaseSnowTown"));
        GenerateBaseSnowTown();
    }
    else if (TempBiome == EHexBiome::Desert || TempBiome == EHexBiome::DesertHill || TempBiome == EHexBiome::DesertHillWood ||
             TempBiome == EHexBiome::DesertWood)
    {
        UE_LOG(LogTemp, Warning, TEXT("GenerateBaseDesertTown"));
        GenerateBaseDesertTown();
    }
    else if (TempBiome == EHexBiome::Meadow || TempBiome == EHexBiome::MeadowHill || TempBiome == EHexBiome::MeadowHillWood ||
             TempBiome == EHexBiome::MeadowWood)
    {
        UE_LOG(LogTemp, Warning, TEXT("GenerateBaseMeadowTown"));
        GenerateBaseMeadowTown();
    }
}

void ACCTownHexagonActor::BeginPlay()
{
    Super::BeginPlay();
}

TArray<ACCSpawnPointBuildActor*> ACCTownHexagonActor::ResetAllSpawnPoint()
{
    UE_LOG(LogTemp, Warning, TEXT("ResetAllSpawnPoint"));
    TArray<AActor*> OutActor;
    TArray<ACCSpawnPointBuildActor*> SpawnArrayActor;
    GetAllChildActors(OutActor);
    if (!OutActor.IsEmpty())
    {
        for (AActor* Element : OutActor)
        {
            if (ACCSpawnPointBuildActor* TempActor = Cast<ACCSpawnPointBuildActor>(Element))
            {
                TempActor->ClearSpawnPoint();
                SpawnArrayActor.Add(TempActor);
            }
        }
    }
    UE_LOG(LogTemp, Display, TEXT("NewTown have %i SpawnPoint"), SpawnArrayActor.Num());
    return SpawnArrayActor;
}

void ACCTownHexagonActor::GenerateBaseSnowTown()
{
    TArray<ACCSpawnPointBuildActor*> SpawnArrayActor;
    SpawnArrayActor = ResetAllSpawnPoint();
    if (!SpawnArrayActor.IsEmpty())
    {
        if (ACCBaseHexagonActor* OwnerHexManager = Cast<ACCBaseHexagonActor>(GetOwner()))
        {
            UE_LOG(LogTemp, Display, TEXT("ACCBaseHexagonActor owner valid"));
            FMeshData OwnerMeshData = OwnerHexManager->GetMeshData();
            MeshLocation->SetStaticMesh(OwnerMeshData.SnowMeshArray[int(FMath::RandRange(0, OwnerMeshData.SnowMeshArray.Num() - 1))]);
        }
        if (UCCGameInstance* CurentGameInstance = Cast<UCCGameInstance>(GetGameInstance()))
        {
            for (int32 i = 0; i < 10; i++)
            {
                if (SpawnArrayActor.IsValidIndex(i))
                {
                    FBuildMeshData BuildData = CurentGameInstance->GetBuildMeshData();
                    SpawnArrayActor[i]->SetNewBuildMesh(
                        BuildData.SSnowBuildArray[int(FMath::RandRange(0, BuildData.SSnowBuildArray.Num() - 1))].LoadSynchronous());
                }
            }
        }
    }
}

void ACCTownHexagonActor::GenerateBaseDesertTown()
{
    TArray<ACCSpawnPointBuildActor*> SpawnArrayActor;
    SpawnArrayActor = ResetAllSpawnPoint();
    if (!SpawnArrayActor.IsEmpty())
    {
        if (ACCBaseHexagonActor* OwnerHexManager = Cast<ACCBaseHexagonActor>(GetOwner()))
        {
            UE_LOG(LogTemp, Display, TEXT("ACCBaseHexagonActor owner valid"));
            FMeshData OwnerMeshData = OwnerHexManager->GetMeshData();
            MeshLocation->SetStaticMesh(OwnerMeshData.DesertMeshArray[int(FMath::RandRange(0, OwnerMeshData.DesertMeshArray.Num() - 1))]);
        }
        if (UCCGameInstance* CurentGameInstance = Cast<UCCGameInstance>(GetGameInstance()))
        {
            for (int32 i = 0; i < 10; i++)
            {
                if (SpawnArrayActor.IsValidIndex(i))
                {
                    FBuildMeshData BuildData = CurentGameInstance->GetBuildMeshData();
                    SpawnArrayActor[i]->SetNewBuildMesh(
                        BuildData.SDesertBuildArray[int(FMath::RandRange(0, BuildData.SDesertBuildArray.Num() - 1))].LoadSynchronous());
                }
            }
        }
    }
}

void ACCTownHexagonActor::GenerateBaseMeadowTown()
{
    TArray<ACCSpawnPointBuildActor*> SpawnArrayActor;
    SpawnArrayActor = ResetAllSpawnPoint();
    if (!SpawnArrayActor.IsEmpty())
    {
        if (ACCBaseHexagonActor* OwnerHexManager = Cast<ACCBaseHexagonActor>(GetOwner()))
        {
            UE_LOG(LogTemp, Display, TEXT("ACCBaseHexagonActor owner valid"));
            FMeshData OwnerMeshData = OwnerHexManager->GetMeshData();
            MeshLocation->SetStaticMesh(OwnerMeshData.MeadowMeshArray[int(FMath::RandRange(0, OwnerMeshData.MeadowMeshArray.Num() - 1))]);
        }
        if (UCCGameInstance* CurentGameInstance = Cast<UCCGameInstance>(GetGameInstance()))
        {
            for (int32 i = 0; i < 10; i++)
            {
                if (SpawnArrayActor.IsValidIndex(i))
                {
                    FBuildMeshData BuildData = CurentGameInstance->GetBuildMeshData();
                    SpawnArrayActor[i]->SetNewBuildMesh(
                        BuildData.SMeadowBuildArray[int(FMath::RandRange(0, BuildData.SMeadowBuildArray.Num() - 1))].LoadSynchronous());
                }
            }
        }
    }
}
