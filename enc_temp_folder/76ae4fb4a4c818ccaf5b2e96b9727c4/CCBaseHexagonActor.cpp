// Fill out your copyright notice in the Description page of Project Settings.

#include "CCBaseHexagonActor.h"
#include "CCItemHexagonActor.h"

ACCBaseHexagonActor::ACCBaseHexagonActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ACCBaseHexagonActor::BeginPlay()
{
    Super::BeginPlay();
    InitMap(200);
}

void ACCBaseHexagonActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACCBaseHexagonActor::InitMap(int32 Offset)
{
    int32 IndexX = 0;
    int32 IndexY = 0;
    FActorSpawnParameters SpawnParams;
    int32 MaxRow = 10;
    for (int32 i = 0; i < MaxRow; i++)
    {
        IndexX = 0 - i;
        auto StartLocaion = GetActorLocation();
        auto StartRotation = GetActorRotation();
        StartLocaion.X += (Offset / 4 + Offset / 2) * i;
        if (i % 2 != 0)
        {
            StartLocaion.Y += (FMath::Sqrt(3) / 2 * 100);
        }
        for (int32 n = 0; n < MaxRow; n++)
        {
            const auto TempHex = GetWorld()->SpawnActor<ACCItemHexagonActor>(HexClass, StartLocaion, StartRotation);
            StartLocaion.Y += FMath::Sqrt(3) / 2 * Offset;
            TempHex->UpdatePosition(IndexX, IndexY);
            IndexX++;
        }
        IndexY++;
    }
    IndexX = 0;
    IndexY = 0;
    for (int32 i = 0; i < MaxRow; i++)
    {
        IndexX = 0 - i;
        auto StartLocaion = GetActorLocation();
        auto StartRotation = GetActorRotation();
        StartLocaion.X += (Offset / 4 + Offset / 2) * i;
        if (i % 2 != 0)
        {
            StartLocaion.Y += (FMath::Sqrt(3) / 2 * 100);
        }
        for (int32 n = 0; n < MaxRow; n++)
        {
            if (n != 0)
            {
                const auto TempHex = GetWorld()->SpawnActor<ACCItemHexagonActor>(HexClass, StartLocaion, StartRotation);
                TempHex->UpdatePosition(IndexX, IndexY);
            }
            StartLocaion.Y -= FMath::Sqrt(3) / 2 * Offset;
            IndexX--;
        }
        IndexY++;
    }
    IndexX = 0;
    IndexY = 0;
    for (int32 i = 0; i < MaxRow; i++)
    {
        IndexX = 0;
        auto StartLocaion = GetActorLocation();
        auto StartRotation = GetActorRotation();
        StartLocaion.X -= (Offset / 4 + Offset / 2) * i;
        if (i % 2 != 0)
        {
            StartLocaion.Y += (FMath::Sqrt(3) / 2 * 100);
        }
        for (int32 n = 0; n < MaxRow; n++)
        {
            if (n != 0)
            {
                const auto TempHex = GetWorld()->SpawnActor<ACCItemHexagonActor>(HexClass, StartLocaion, StartRotation);
                TempHex->UpdatePosition(IndexX, IndexY);
            }
            StartLocaion.Y -= FMath::Sqrt(3) / 2 * Offset;
            IndexX++;
        }
        IndexY--;
    }
}
