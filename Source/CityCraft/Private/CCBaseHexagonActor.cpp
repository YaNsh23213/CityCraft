// Fill out your copyright notice in the Description page of Project Settings.

#include "CCBaseHexagonActor.h"
#include "CCItemHexagonActor.h"
#include "Components/StaticMeshComponent.h"
#include "CCGameInstance.h"
#include "Player/CCMainGameMode.h"

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

void ACCBaseHexagonActor::OnConstruction(const FTransform& Transform)
{
    // InitMap(HexDiameterC, MaxYC, MaxXC);
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

            StartLocaion.Y += (FMath::Sqrt(3) / 2 * (HexDiameter / 2));
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
            HexArray.Add(TempHex);
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
            StartLocaion.Y += (FMath::Sqrt(3) / 2 * (HexDiameter / 2));
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
                HexArray.Add(TempHex);
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
                StartLocaion.Y -= (FMath::Sqrt(3) / 2 * (HexDiameter / 2));
                CenterIndexOffset--;
            }

            for (int32 n = 0; n < MaxX; n++)
            {
                if (n != 0)
                {
                    const auto TempHex = GetWorld()->SpawnActor<ACCItemHexagonActor>(HexClass, StartLocaion, StartRotation);
                    TempHex->UpdatePosition(IndexX, IndexY);
                    HexArray.Add(TempHex);
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
            StartLocaion.Y -= (FMath::Sqrt(3) / 2 * (HexDiameter / 2));
            CenterIndexOffset--;
        }

        for (int32 n = 0; n < MaxX; n++)
        {
            if (i != 0)
            {
                const auto TempHex = GetWorld()->SpawnActor<ACCItemHexagonActor>(HexClass, StartLocaion, StartRotation);
                TempHex->UpdatePosition(IndexX, IndexY);
                HexArray.Add(TempHex);
                StartLocaion.Y -= FMath::Sqrt(3) / 2 * HexDiameter;
                IndexX--;
            }
        }
        IndexY--;
    }
    StartGenerate();
}

void ACCBaseHexagonActor::StartGenerate()
{
    int32 MaxBoundX = FindMinMax(true, true);
    int32 MinBoundX = FindMinMax(true, false);
    int32 MaxBoundY = FindMinMax(false, true);
    int32 MinBoundY = FindMinMax(false, false);

    int32 SnowBorder = FMath::RoundToInt(MaxBoundY - float(MaxBoundY) * PercentSnow);
    int32 DesertBorder = FMath::RoundToInt(float(MaxBoundY) * PercentDesert);
    UE_LOG(LogTemp, Display, TEXT("SnowBorder %i"), SnowBorder);
    UE_LOG(LogTemp, Display, TEXT("DesertBorder %i"), DesertBorder);

    // Init first world
    for (auto Element : HexArray)
    {
        UMaterialInstanceDynamic* TempMaterial = Cast<UMaterialInstanceDynamic>(Element->GetHexMesh()->GetMaterial(0));
        if (TempMaterial)
        {
            // Generate SnowLocation
            if (PercentSnow > 0)
            {
                if (Element->GetPosition().Y >= SnowBorder)
                {
                    // TO DO Action Mesh
                    Element->MeshLocation->SetStaticMesh(
                        DataMesh.SnowMeshArray[int(FMath::RandRange(0, DataMesh.SnowMeshArray.Num() - 1))]);
                    TempMaterial->SetVectorParameterValue("Type", FColor::White);
                    Element->SetHexBiome(EHexBiome::Snow);
                    continue;
                }

                if (Element->GetPosition().Y <= -SnowBorder)
                {
                    Element->MeshLocation->SetStaticMesh(
                        DataMesh.SnowMeshArray[int(FMath::RandRange(0, DataMesh.SnowMeshArray.Num() - 1))]);
                    TempMaterial->SetVectorParameterValue("Type", FColor::White);
                    Element->SetHexBiome(EHexBiome::Snow);
                    continue;
                }
            }
            // Generate DesertLocation
            if (PercentDesert > 0)
            {
                if (Element->GetPosition().Y <= DesertBorder && Element->GetPosition().Y >= -DesertBorder)
                {
                    // TO DO Action Mesh
                    Element->MeshLocation->SetStaticMesh(
                        DataMesh.DesertMeshArray[int(FMath::RandRange(0, DataMesh.DesertMeshArray.Num() - 1))]);
                    TempMaterial->SetVectorParameterValue("Type", FColor::Yellow);
                    Element->SetHexBiome(EHexBiome::Desert);
                    continue;
                }
            }
            // Generate MeadowLocation
            Element->MeshLocation->SetStaticMesh(DataMesh.MeadowMeshArray[int(FMath::RandRange(0, DataMesh.MeadowMeshArray.Num() - 1))]);
            TempMaterial->SetVectorParameterValue("Type", FColor::Green);
            Element->SetHexBiome(EHexBiome::Meadow);
        }
    }
    // ItinOverlap
    // MainOveralpSnow
    if (PercentSnow > 0 && PercentSnowOverlap > 0)
    {
        int32 PersentOverlapSnowBiome =
            FMath::Clamp(FMath::RoundToInt(float(MaxBoundY) * PercentSnow * PercentSnowOverlap), MinOverlapAmount, MaxOverlapAmount);

        UE_LOG(LogTemp, Display, TEXT("PersentOverlapSnowBiome %i"), PersentOverlapSnowBiome);
        for (auto Element : HexArray)
        {
            UMaterialInstanceDynamic* TempMaterial = Cast<UMaterialInstanceDynamic>(Element->GetHexMesh()->GetMaterial(0));
            int32 Min = 0;
            int32 Max = 0;
            int32 ChangeToOverlap = 0;
            int32 MaxCont = 0;
            if (Element->GetPosition().Y >= SnowBorder - PersentOverlapSnowBiome &&
                Element->GetPosition().Y <= SnowBorder + PersentOverlapSnowBiome)
            {
                Min = SnowBorder - PersentOverlapSnowBiome;
                Max = SnowBorder + PersentOverlapSnowBiome;
                MaxCont = PersentOverlapSnowBiome * 2 + 1;
                for (int32 i = 0; i < MaxCont; i++)
                {
                    if (Element->GetPosition().Y == Min + i)
                    {
                        ChangeToOverlap = float(float(i) / (float(PersentOverlapSnowBiome) * 2 + 1)) * 100 + 5;
                        break;
                    }
                }
                int32 RandNumber = FMath::RandRange(0, 100);
                UE_LOG(LogTemp, Display, TEXT("RandNumber %i ChangeToOverlap %i"), RandNumber, ChangeToOverlap);
                if (RandNumber < ChangeToOverlap)
                {
                    Element->MeshLocation->SetStaticMesh(
                        DataMesh.SnowMeshArray[int(FMath::RandRange(0, DataMesh.SnowMeshArray.Num() - 1))]);
                    TempMaterial->SetVectorParameterValue("Type", FColor::White);
                    Element->SetHexBiome(EHexBiome::Snow);
                }
                else
                {
                    Element->MeshLocation->SetStaticMesh(
                        DataMesh.MeadowMeshArray[int(FMath::RandRange(0, DataMesh.MeadowMeshArray.Num() - 1))]);
                    TempMaterial->SetVectorParameterValue("Type", FColor::Green);
                    Element->SetHexBiome(EHexBiome::Meadow);
                }
            }
            if (Element->GetPosition().Y >= -SnowBorder - PersentOverlapSnowBiome &&
                Element->GetPosition().Y <= -SnowBorder + PersentOverlapSnowBiome)
            {

                Min = -SnowBorder + PersentOverlapSnowBiome;
                Max = -SnowBorder - PersentOverlapSnowBiome;
                MaxCont = PersentOverlapSnowBiome * 2 + 1;
                for (int32 i = 0; i < MaxCont; i++)
                {
                    if (Element->GetPosition().Y == Min - i)
                    {
                        ChangeToOverlap = +float(float(i) / (float(PersentOverlapSnowBiome) * 2 + 1)) * 100 + 5;
                        break;
                    }
                }
                int32 RandNumber = FMath::RandRange(0, 100);
                UE_LOG(LogTemp, Display, TEXT("RandNumber %i ChangeToOverlap %i"), RandNumber, ChangeToOverlap);
                if (RandNumber < ChangeToOverlap)
                {
                    Element->MeshLocation->SetStaticMesh(
                        DataMesh.SnowMeshArray[int(FMath::RandRange(0, DataMesh.SnowMeshArray.Num() - 1))]);
                    TempMaterial->SetVectorParameterValue("Type", FColor::White);
                    Element->SetHexBiome(EHexBiome::Snow);
                }
                else
                {
                    Element->MeshLocation->SetStaticMesh(
                        DataMesh.MeadowMeshArray[int(FMath::RandRange(0, DataMesh.MeadowMeshArray.Num() - 1))]);
                    TempMaterial->SetVectorParameterValue("Type", FColor::Green);
                    Element->SetHexBiome(EHexBiome::Meadow);
                }
            }
        }
    }
    // ItinOverlap
    // MainOveralpDesert
    if (PercentDesert > 0 && PercentDesertOverlap > 0)
    {
        int32 PersentOverlapDesertBiome =
            FMath::Clamp(FMath::RoundToInt(float(MaxBoundY) * PercentDesert * PercentDesertOverlap), MinOverlapAmount, MaxOverlapAmount);

        UE_LOG(LogTemp, Display, TEXT("PersentOverlapSnowBiome %i"), PersentOverlapDesertBiome);
        for (auto Element : HexArray)
        {
            UMaterialInstanceDynamic* TempMaterial = Cast<UMaterialInstanceDynamic>(Element->GetHexMesh()->GetMaterial(0));
            int32 Min = 0;
            int32 Max = 0;
            int32 ChangeToOverlap = 0;
            int32 MaxCont = 0;
            int32 Mid = 0;
            if (Element->GetPosition().Y >= -DesertBorder - PersentOverlapDesertBiome &&
                Element->GetPosition().Y <= DesertBorder + PersentOverlapDesertBiome)
            {
                Min = -DesertBorder - PersentOverlapDesertBiome;
                Max = DesertBorder + PersentOverlapDesertBiome;
                Mid = (Max + Min) / 2;
                MaxCont = PersentOverlapDesertBiome * 2 + 1;
                for (int32 i = 0; i < MaxCont; i++)
                {
                    if (Element->GetPosition().Y == Mid + i)
                    {
                        ChangeToOverlap = 105 - float(float(i) / (float(PersentOverlapDesertBiome) * 2 + 1)) * 100 + 5;
                        break;
                    }
                    else if (Element->GetPosition().Y == Mid - i)
                    {
                        ChangeToOverlap = 105 - +float(float(i) / (float(PersentOverlapDesertBiome) * 2 + 1)) * 100 + 5;
                        break;
                    }
                }
                int32 RandNumber = FMath::RandRange(0, 100);
                if (RandNumber < ChangeToOverlap)
                {
                    Element->MeshLocation->SetStaticMesh(
                        DataMesh.DesertMeshArray[int(FMath::RandRange(0, DataMesh.DesertMeshArray.Num() - 1))]);
                    TempMaterial->SetVectorParameterValue("Type", FColor::Yellow);
                    Element->SetHexBiome(EHexBiome::Desert);
                }
                else
                {
                    if (Element->GetHexBiome() == EHexBiome::Desert)
                    {
                        Element->MeshLocation->SetStaticMesh(
                            DataMesh.MeadowMeshArray[int(FMath::RandRange(0, DataMesh.MeadowMeshArray.Num() - 1))]);
                        TempMaterial->SetVectorParameterValue("Type", FColor::Green);
                        Element->SetHexBiome(EHexBiome::Meadow);
                    }
                }
            }
        }
    }

    // Watter
    if (HaveOcean)
    {
        int32 StartPoint = 0;
        int32 OffsetStartPoint = 0;
        int32 OceanMedianaAmount = 0;
        FVector2D CurrentIndex = {0, 0};
        ACCItemHexagonActor *CurrentItem, *NarcoalCurrentItem = nullptr;
        UMaterialInstanceDynamic* TempMaterial = nullptr;
        for (int32 n = 0; n < MaxBoundY + 2; n++)
        {
            CurrentItem = GetHexFromIdex(CurrentIndex);
            if (CurrentItem)
            {
                UE_LOG(LogTemp, Warning, TEXT("True CurrentIndex %s CurrentItem %s"), *CurrentIndex.ToString(),
                    *CurrentItem->GetPosition().ToString())
                TempMaterial = Cast<UMaterialInstanceDynamic>(CurrentItem->GetHexMesh()->GetMaterial(0));
                TempMaterial->SetVectorParameterValue("Type", FColor::Blue);
                CurrentItem->SetHexBiome(EHexBiome::Ocean);
            }
            if (n % 2 != 0)
            {
                // CurrentIndex.X += 1;
                CurrentIndex.Y += 1;
            }
            else
            {
                if (n != 0)
                {
                    CurrentIndex.X -= 1;
                    CurrentIndex.Y += 1;
                }
            }
        }
        CurrentIndex = {0, 0};
        for (int32 n = 0; n < MaxBoundY + 2; n++)
        {
            NarcoalCurrentItem = GetHexFromIdex(CurrentIndex);
            if (NarcoalCurrentItem)
            {
                UE_LOG(LogTemp, Warning, TEXT("True CurrentIndex %s CurrentItem %s"), *CurrentIndex.ToString(),
                    *NarcoalCurrentItem->GetPosition().ToString())
                TempMaterial = Cast<UMaterialInstanceDynamic>(NarcoalCurrentItem->GetHexMesh()->GetMaterial(0));
                TempMaterial->SetVectorParameterValue("Type", FColor::Blue);
                NarcoalCurrentItem->SetHexBiome(EHexBiome::Ocean);
            }
            if (n % 2 != 0)
            {
                CurrentIndex.Y -= 1;
                CurrentIndex.X += 1;
            }
            else
            {
                if (n != 0)
                {
                    // CurrentIndex.X += 1;
                    CurrentIndex.Y -= 1;
                }
            }
        }
    }

    // HillGenerate
    TArray<ACCItemHexagonActor*> DesertArr;
    TArray<ACCItemHexagonActor*> SnowArr;
    TArray<ACCItemHexagonActor*> MeadowArr;
    for (auto Element : HexArray)
    {
        switch (Element->GetHexBiome())
        {
            case EHexBiome::Snow: SnowArr.Add(Element); break;
            case EHexBiome::Meadow: MeadowArr.Add(Element); break;
            case EHexBiome::Desert: DesertArr.Add(Element); break;
        }
    }
    int32 i = 0;
    // DesertHill
    float DesrtHillFr = DesertArr.Num() * DesertHilFrequency;
    while (i < DesrtHillFr)
    {
        int32 TempIndex = FMath::RandRange(0, DesertArr.Num() - 1);
        if (DesertArr.IsValidIndex(TempIndex))
        {
            DesertArr[TempIndex]->SetHexBiome(EHexBiome::DesertHill);
            DesertArr[TempIndex]->MeshLocation->SetStaticMesh(
                DataMesh.DesertHillMeshArray[int(FMath::RandRange(0, DataMesh.DesertHillMeshArray.Num() - 1))]);
            DesertArr.RemoveAt(TempIndex);
        }
        i++;
    }
    // SnowHill
    i = 0;
    float SnowArrHillFr = SnowArr.Num() * SnowHilFrequency;
    while (i < SnowArrHillFr)
    {
        int32 TempIndex = FMath::RandRange(0, SnowArr.Num());
        if (SnowArr.IsValidIndex(TempIndex))
        {
            SnowArr[TempIndex]->SetHexBiome(EHexBiome::SnowHill);
            SnowArr[TempIndex]->MeshLocation->SetStaticMesh(
                DataMesh.SnowHillMeshArray[int(FMath::RandRange(0, DataMesh.SnowHillMeshArray.Num() - 1))]);
            SnowArr.RemoveAt(TempIndex);
        }
        i++;
    }
    // MeadowHill
    i = 0;
    float MeadowArrlFr = MeadowArr.Num() * MeadowHilFrequency;
    while (i < MeadowArrlFr)
    {
        int32 TempIndex = FMath::RandRange(0, MeadowArr.Num() - 1);
        if (MeadowArr.IsValidIndex(TempIndex))
        {
            MeadowArr[TempIndex]->SetHexBiome(EHexBiome::MeadowHill);
            MeadowArr[TempIndex]->MeshLocation->SetStaticMesh(
                DataMesh.MeadowHillMeshArray[int(FMath::RandRange(0, DataMesh.MeadowHillMeshArray.Num() - 1))]);
            MeadowArr.RemoveAt(TempIndex);
        }
        i++;
    }
    // WoodGenerate
    TArray<ACCItemHexagonActor*> WoodDesertArr;
    TArray<ACCItemHexagonActor*> WoodSnowArr;
    TArray<ACCItemHexagonActor*> WoodMeadowArr;
    for (auto ElementWood : HexArray)
    {
        switch (ElementWood->GetHexBiome())
        {
            case EHexBiome::Snow: WoodSnowArr.Add(ElementWood); break;
            case EHexBiome::Meadow: WoodMeadowArr.Add(ElementWood); break;
            case EHexBiome::Desert: WoodDesertArr.Add(ElementWood); break;
            case EHexBiome::SnowHill: WoodSnowArr.Add(ElementWood); break;
            case EHexBiome::MeadowHill: WoodMeadowArr.Add(ElementWood); break;
            case EHexBiome::DesertHill: WoodDesertArr.Add(ElementWood); break;
        }
    }
    // DesertWood
    i = 0;
    float WoodDesrtHillFr = WoodDesertArr.Num() * DesertWoodFrequency;
    while (i < WoodDesrtHillFr)
    {
        int32 TempIndex = FMath::RandRange(0, WoodDesertArr.Num() - 1);
        if (WoodDesertArr.IsValidIndex(TempIndex))
        {
            if (WoodDesertArr[TempIndex]->GetHexBiome() == EHexBiome::Desert)
            {
                WoodDesertArr[TempIndex]->SetHexBiome(EHexBiome::DesertWood);
                WoodDesertArr[TempIndex]->MeshLocation->SetStaticMesh(
                    DataMesh.DesertWoodMeshArray[int(FMath::RandRange(0, DataMesh.DesertWoodMeshArray.Num() - 1))]);
            }
            else
            {
                WoodDesertArr[TempIndex]->SetHexBiome(EHexBiome::DesertHillWood);
                WoodDesertArr[TempIndex]->MeshLocation->SetStaticMesh(
                    DataMesh.DesertHillWoodMeshArray[int(FMath::RandRange(0, DataMesh.DesertHillWoodMeshArray.Num() - 1))]);
            }
            WoodDesertArr.RemoveAt(TempIndex);
        }
        i++;
    }
    // SnowWood
    i = 0;
    float WoodSnowArrHillFr = WoodSnowArr.Num() * SnowWoodFrequency;
    UE_LOG(LogTemp, Warning, TEXT("Num ARRAY SNOW %i"), WoodSnowArr.Num());
    while (i < WoodSnowArrHillFr)
    {
        int32 TempIndex = FMath::RandRange(0, WoodSnowArr.Num() - 1);
        UE_LOG(LogTemp, Warning, TEXT("index %i"), TempIndex);
        if (WoodSnowArr.IsValidIndex(TempIndex))
        {
            if (WoodSnowArr[TempIndex]->GetHexBiome() == EHexBiome::Snow)
            {
                WoodSnowArr[TempIndex]->SetHexBiome(EHexBiome::SnowWood);
                WoodSnowArr[TempIndex]->MeshLocation->SetStaticMesh(
                    DataMesh.SnowWoodMeshArray[int(FMath::RandRange(0, DataMesh.SnowWoodMeshArray.Num() - 1))]);
            }
            else
            {
                WoodSnowArr[TempIndex]->SetHexBiome(EHexBiome::SnowHillWood);
                WoodSnowArr[TempIndex]->MeshLocation->SetStaticMesh(
                    DataMesh.SnowHillWoodMeshArray[int(FMath::RandRange(0, DataMesh.SnowHillWoodMeshArray.Num() - 1))]);
            }
            WoodSnowArr.RemoveAt(TempIndex);
        }
        i++;
    }
    // MeadowHill
    i = 0;
    float WoodMeadowArrlFr = WoodMeadowArr.Num() * MeadowWoodFrequency;
    while (i < WoodMeadowArrlFr)
    {
        int32 TempIndex = FMath::RandRange(0, WoodMeadowArr.Num() - 1);
        if (WoodMeadowArr.IsValidIndex(TempIndex))
        {
            if (WoodMeadowArr[TempIndex]->GetHexBiome() == EHexBiome::Meadow)
            {
                WoodMeadowArr[TempIndex]->SetHexBiome(EHexBiome::DesertWood);
                WoodMeadowArr[TempIndex]->MeshLocation->SetStaticMesh(
                    DataMesh.MeadowWoodMeshArray[int(FMath::RandRange(0, DataMesh.MeadowWoodMeshArray.Num() - 1))]);
            }
            else
            {
                WoodMeadowArr[TempIndex]->SetHexBiome(EHexBiome::MeadowHillWood);
                WoodMeadowArr[TempIndex]->MeshLocation->SetStaticMesh(
                    DataMesh.MeadowHillWoodMeshArray[int(FMath::RandRange(0, DataMesh.MeadowHillWoodMeshArray.Num() - 1))]);
            }
            WoodMeadowArr.RemoveAt(TempIndex);
        }
        i++;
    }
    // LakeGenerate
    if (AmountLake > 0)
    {
        TArray<int32> LakeIndex;
        bool ValidIndex = false;
        for (int32 n = 0; n < AmountLake; n++)
        {
            while (!ValidIndex)
            {
                int32 TempIndexLake = FMath::RandRange(0, HexArray.Num() - 1);
                for (int32 Temp : LakeIndex)
                {
                    if (Temp == TempIndexLake)
                    {
                        continue;
                    }
                }
                LakeIndex.Add(TempIndexLake);
                ValidIndex = true;
                HexArray[TempIndexLake]->MeshLocation->SetStaticMesh(
                    DataMesh.LakeMeshArray[int(FMath::RandRange(0, DataMesh.LakeMeshArray.Num() - 1))]);
                HexArray[TempIndexLake]->SetHexBiome(EHexBiome::Lake);
            }
            ValidIndex = false;
        }
        for (int32 TempIndex : LakeIndex)
        {
            auto FirstRadiusArray = GetFirstRadiusHex(HexArray[TempIndex]);
            auto SecondRadiusArray = GetSecondRadiusHex(HexArray[TempIndex]);
            auto ThirdRadiusArray = GetThirdRadiusHex(HexArray[TempIndex]);

            for (auto RadiusElement : FirstRadiusArray)
            {
                if (FMath::FRandRange(0.0f, 1.0f) < StartedChanceUpLake)
                {
                    RadiusElement.HexRadius->MeshLocation->SetStaticMesh(
                        DataMesh.LakeMeshArray[int(FMath::RandRange(0, DataMesh.LakeMeshArray.Num() - 1))]);
                    RadiusElement.HexRadius->SetHexBiome(EHexBiome::Lake);
                }
            }

            for (auto RadiusElement : SecondRadiusArray)
            {
                auto TempRadius = GetFirstRadiusHex(RadiusElement.HexRadius);
                for (auto TempRadiusElement : TempRadius)
                {
                    if (TempRadiusElement.HexRadius->GetHexBiome() == EHexBiome::Lake)
                    {
                        if (FMath::FRandRange(0.0f, 1.0f) < FMath::Clamp(StartedChanceUpLake - StepChanceDownLake, 0.0f, 10.0f))
                        {
                            RadiusElement.HexRadius->MeshLocation->SetStaticMesh(
                                DataMesh.LakeMeshArray[int(FMath::RandRange(0, DataMesh.LakeMeshArray.Num() - 1))]);
                            RadiusElement.HexRadius->SetHexBiome(EHexBiome::Lake);
                            break;
                        }
                    }
                }
            }
            for (auto RadiusElement : ThirdRadiusArray)
            {
                auto TempRadius = GetFirstRadiusHex(RadiusElement.HexRadius);
                for (auto TempRadiusElement : TempRadius)
                {
                    if (TempRadiusElement.HexRadius->GetHexBiome() == EHexBiome::Lake)
                    {
                        if (FMath::FRandRange(0.0f, 1.0f) <
                            FMath::Clamp(StartedChanceUpLake - StepChanceDownLake - StepChanceDownLake, 0.0f, 10.0f))
                        {
                            RadiusElement.HexRadius->MeshLocation->SetStaticMesh(
                                DataMesh.LakeMeshArray[int(FMath::RandRange(0, DataMesh.LakeMeshArray.Num() - 1))]);
                            RadiusElement.HexRadius->SetHexBiome(EHexBiome::Lake);
                            break;
                        }
                    }
                }
            }
        }
    }
    // ModulLake
    if (NeedGenerateModuleLake)
    {
        TArray<ACCItemHexagonActor*> ArrayHexLake;
        for (auto Lake : HexArray)
        {
            if (Lake->GetHexBiome() == EHexBiome::Lake)
            {
                ArrayHexLake.Add(Lake);
            }
        }
        if (ArrayHexLake.Num())
        {
            for (auto LakeItem : ArrayHexLake)
            {
                auto FirstRadius = GetFirstRadiusHex(LakeItem);
                TArray<int32> ArrayGroundLake;
                for (auto LakeFirstRadius : FirstRadius)
                {
                    if (LakeFirstRadius.HexRadius->GetHexBiome() == EHexBiome::Lake)
                    {
                        ArrayGroundLake.Add(LakeFirstRadius.IndexRadiusHex);
                    }
                }
                for (auto HexModuleLake : LakeModuleCorrection)
                {
                    if (IsEqual(HexModuleLake.ArrayLandIndex, ArrayGroundLake))
                    {
                        LakeItem->MeshLocation->SetStaticMesh(HexModuleLake.LakeMesh);

                        // SetCorrectionRotator
                        auto TempLocation = LakeItem->MeshLocation->GetRelativeRotation();
                        TempLocation.Yaw += HexModuleLake.RotationCorrection - 30;
                        LakeItem->MeshLocation->SetWorldRotation(TempLocation);
                        break;
                    }
                }
                int32 SnowAmount = 0;
                int32 SandAmount = 0;
                int32 MeadowAmount = 0;
                UMaterialInstanceDynamic* TempMat = nullptr;
                TempMat = UMaterialInstanceDynamic::Create(Cast<UMaterial>(LakeItem->MeshLocation->GetMaterial(0)), this);
                LakeItem->MeshLocation->SetMaterial(0, TempMat);
                for (auto MaterialCorrectionElement : FirstRadius)
                {
                    EHexBiome TempBiome = MaterialCorrectionElement.HexRadius->GetHexBiome();
                    if (TempBiome == EHexBiome::Snow || TempBiome == EHexBiome::SnowHill || TempBiome == EHexBiome::SnowHillWood ||
                        TempBiome == EHexBiome::SnowWood)
                    {
                        SnowAmount++;
                        continue;
                    }
                    else if (TempBiome == EHexBiome::Desert || TempBiome == EHexBiome::DesertHill ||
                             TempBiome == EHexBiome::DesertHillWood || TempBiome == EHexBiome::DesertWood)
                    {
                        SandAmount++;
                        continue;
                    }
                    else if (TempBiome == EHexBiome::Meadow || TempBiome == EHexBiome::MeadowHill ||
                             TempBiome == EHexBiome::MeadowHillWood || TempBiome == EHexBiome::MeadowWood)
                    {
                        MeadowAmount++;
                        continue;
                    }
                }
                if (SnowAmount >= MeadowAmount && SnowAmount > SandAmount)
                {
                    TempMat->SetScalarParameterValue("TypeMat", 1.0f);
                }
                else if (SandAmount >= SnowAmount && SandAmount > MeadowAmount)
                {
                    TempMat->SetScalarParameterValue("TypeMat", 0.5f);
                }
                else if (MeadowAmount >= SnowAmount && MeadowAmount > SandAmount)
                {
                    TempMat->SetScalarParameterValue("TypeMat", 0.0f);
                }
            }
        }
    }
    ACCMainGameMode* GameMode = Cast<ACCMainGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->AfterGeneration(this);
    }
}
int32 ACCBaseHexagonActor::FindMinMax(bool IsX, bool IsMax)
{
    if (!HexArray.Num()) return 0;

    int32 ReturnAmount = 0;

    if (IsX)
    {
        ReturnAmount = HexArray[0]->GetPosition().X;
        if (IsMax)
        {
            for (auto Element : HexArray)
            {
                if (Element->GetPosition().X > ReturnAmount)
                {
                    ReturnAmount = Element->GetPosition().X;
                }
            }
            return ReturnAmount;
        }
        else
        {
            for (auto Element : HexArray)
            {
                if (Element->GetPosition().X < ReturnAmount)
                {
                    ReturnAmount = Element->GetPosition().X;
                }
            }
            return ReturnAmount;
        }
        return int32();
    }
    else
    {
        if (IsMax)
        {
            for (auto Element : HexArray)
            {
                if (Element->GetPosition().Y > ReturnAmount)
                {
                    ReturnAmount = Element->GetPosition().Y;
                }
            }
            return ReturnAmount;
        }
        else
        {
            for (auto Element : HexArray)
            {
                if (Element->GetPosition().Y < ReturnAmount)
                {
                    ReturnAmount = Element->GetPosition().Y;
                }
            }
            return ReturnAmount;
        }
        return 0;
    }
    return 0;
}

ACCItemHexagonActor* ACCBaseHexagonActor::GetHexFromIdex(FVector2D Position)
{
    for (auto Element : HexArray)
    {
        if (Element->GetPosition().X == Position.X && Element->GetPosition().Y == Position.Y)
        {
            return Element;
        }
    }
    return nullptr;
}

TArray<FRadiusReturnHexStruct> ACCBaseHexagonActor::GetFirstRadiusHex(ACCItemHexagonActor* BaseHex)
{
    TArray<FRadiusReturnHexStruct> ReturnArray;
    FVector2D CurrentIndex = BaseHex->GetPosition();
    FRadiusReturnHexStruct Element;
    for (int32 i = 0; i < 6; i++)
    {
        FVector2D AddModfier = FirstRadiusModifier[i];
        Element.HexRadius = GetHexFromIdex({CurrentIndex.X + AddModfier.X, CurrentIndex.Y + AddModfier.Y});
        Element.IndexRadiusHex = i + 1;
        if (Element.HexRadius)
        {
            ReturnArray.Add(Element);
        }
    }
    return ReturnArray;
}

TArray<FRadiusReturnHexStruct> ACCBaseHexagonActor::GetSecondRadiusHex(ACCItemHexagonActor* BaseHex)
{
    TArray<FRadiusReturnHexStruct> ReturnArray;
    FVector2D CurrentIndex = BaseHex->GetPosition();
    FRadiusReturnHexStruct Element;
    for (int32 i = 0; i < 12; i++)
    {
        FVector2D AddModfier = SecondRadiusModifier[i];
        Element.HexRadius = GetHexFromIdex({CurrentIndex.X + AddModfier.X, CurrentIndex.Y + AddModfier.Y});
        Element.IndexRadiusHex = i + 1;
        if (Element.HexRadius)
        {
            ReturnArray.Add(Element);
        }
    }
    return ReturnArray;
}

TArray<FRadiusReturnHexStruct> ACCBaseHexagonActor::GetThirdRadiusHex(ACCItemHexagonActor* BaseHex)
{
    TArray<FRadiusReturnHexStruct> ReturnArray;
    FVector2D CurrentIndex = BaseHex->GetPosition();
    FRadiusReturnHexStruct Element;
    for (int32 i = 0; i < 18; i++)
    {
        FVector2D AddModfier = ThirdRadiusModifier[i];
        Element.HexRadius = GetHexFromIdex({CurrentIndex.X + AddModfier.X, CurrentIndex.Y + AddModfier.Y});
        Element.IndexRadiusHex = i + 1;
        if (Element.HexRadius)
        {
            ReturnArray.Add(Element);
        }
    }
    return ReturnArray;
}

bool ACCBaseHexagonActor::IsEqual(TArray<int32> Array1, TArray<int32> Array2)
{
    if (Array1.Num() == Array2.Num())
    {
        for (int32 i = 0; i < Array1.Num(); i++)
        {
            if (Array1[i] != Array2[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
