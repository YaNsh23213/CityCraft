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
    InitMap(HexDiameterC, MaxYC, MaxXC);
}

void ACCBaseHexagonActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACCBaseHexagonActor::InitMap(int32 HexDiameter, int32 MaxY, int32 MaxX)
{
    int32 IndexX = 0;
    int32 IndexY = 0;
    FActorSpawnParameters SpawnParams;
    int32 CenterIndexOffset = 0;
    // ToRight
    for (int32 i = 0; i < MaxY; i++)
    {
        IndexX = 0 - CenterIndexOffset;
        auto StartLocaion = GetActorLocation();
        auto StartRotation = GetActorRotation();
        StartLocaion.X += (HexDiameter / 4 + HexDiameter / 2) * i;
        if (i % 2 != 0)
        {

            StartLocaion.Y += (FMath::Sqrt(3) / 2 * 100);
            if (i != 0)
            {
                CenterIndexOffset++;
            }
        }

        for (int32 n = 0; n < MaxX; n++)
        {
            const auto TempHex = GetWorld()->SpawnActor<ACCItemHexagonActor>(HexClass, StartLocaion, StartRotation);
            StartLocaion.Y += FMath::Sqrt(3) / 2 * HexDiameter;
            TempHex->UpdatePosition(IndexX, IndexY);
            IndexX++;
        }
        IndexY++;
    }
    // TopLeft
    IndexX = 0;
    IndexY = 0;
    CenterIndexOffset = 0;
    for (int32 i = 0; i < MaxY; i++)
    {
        IndexX = 0 - CenterIndexOffset;
        auto StartLocaion = GetActorLocation();
        auto StartRotation = GetActorRotation();
        StartLocaion.X += (HexDiameter / 4 + HexDiameter / 2) * i;
        if (i % 2 != 0)
        {
            StartLocaion.Y += (FMath::Sqrt(3) / 2 * 100);
            if (i != 0)
            {
                CenterIndexOffset++;
            }
        }
        for (int32 n = 0; n < MaxX; n++)
        {
            if (n != 0)
            {
                const auto TempHex = GetWorld()->SpawnActor<ACCItemHexagonActor>(HexClass, StartLocaion, StartRotation);
                TempHex->UpdatePosition(IndexX, IndexY);
            }
            StartLocaion.Y -= FMath::Sqrt(3) / 2 * HexDiameter;
            IndexX--;
        }
        IndexY++;
    }
    // BottomRight
    IndexX = 0;
    IndexY = 0;
    CenterIndexOffset = 0;
    for (int32 i = 0; i < MaxY; i++)
    {
        IndexX = 0 - CenterIndexOffset;
        auto StartLocaion = GetActorLocation();
        auto StartRotation = GetActorRotation();
        StartLocaion.X -= (HexDiameter / 4 + HexDiameter / 2) * i;
        if (i != 0)
        {
            if (i % 2 != 0)
            {
                StartLocaion.Y -= (FMath::Sqrt(3) / 2 * 100);
                CenterIndexOffset--;
            }

            for (int32 n = 0; n < MaxX; n++)
            {
                if (n != 0)
                {
                    const auto TempHex = GetWorld()->SpawnActor<ACCItemHexagonActor>(HexClass, StartLocaion, StartRotation);
                    TempHex->UpdatePosition(IndexX, IndexY);
                }
                StartLocaion.Y += FMath::Sqrt(3) / 2 * HexDiameter;
                IndexX++;
            }
            IndexY--;
        }
        else
        {
            IndexY--;
        }
    }
    // BottomLeft
    IndexX = 0;
    IndexY = 0;
    CenterIndexOffset = 0;
    for (int32 i = 0; i < MaxY; i++)
    {
        IndexX = 0 - CenterIndexOffset;
        auto StartLocaion = GetActorLocation();
        auto StartRotation = GetActorRotation();
        StartLocaion.X -= (HexDiameter / 4 + HexDiameter / 2) * i;

        if (i % 2 != 0)
        {
            StartLocaion.Y -= (FMath::Sqrt(3) / 2 * 100);
            CenterIndexOffset--;
        }

        for (int32 n = 0; n < MaxX; n++)
        {

            const auto TempHex = GetWorld()->SpawnActor<ACCItemHexagonActor>(HexClass, StartLocaion, StartRotation);
            TempHex->UpdatePosition(IndexX, IndexY);
            StartLocaion.Y -= FMath::Sqrt(3) / 2 * HexDiameter;
            IndexX--;
        }
        IndexY--;
    }
}
