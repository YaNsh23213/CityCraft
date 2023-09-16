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
                StartLocaion.Y -= (FMath::Sqrt(3) / 2 * 100);
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
            StartLocaion.Y -= (FMath::Sqrt(3) / 2 * 100);
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

                    TempMaterial->SetVectorParameterValue("Type", FColor::White);
                    Element->SetHexBiome(EHexBiome::Snow);
                    continue;
                }

                if (Element->GetPosition().Y <= -SnowBorder)
                {

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

                    TempMaterial->SetVectorParameterValue("Type", FColor::Yellow);
                    Element->SetHexBiome(EHexBiome::Desert);
                    continue;
                }
            }
            // Generate MeadowLocation
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
                    TempMaterial->SetVectorParameterValue("Type", FColor::White);
                    Element->SetHexBiome(EHexBiome::Snow);
                }
                else
                {
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
                    TempMaterial->SetVectorParameterValue("Type", FColor::White);
                    Element->SetHexBiome(EHexBiome::Snow);
                }
                else
                {
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
                UE_LOG(LogTemp, Display, TEXT("Mid %i"), Mid);
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
                    TempMaterial->SetVectorParameterValue("Type", FColor::Yellow);
                    Element->SetHexBiome(EHexBiome::Desert);
                }
                else
                {
                    if (Element->GetHexBiome() == EHexBiome::Desert)
                    {
                        TempMaterial->SetVectorParameterValue("Type", FColor::Green);
                        Element->SetHexBiome(EHexBiome::Meadow);
                    }
                }
            }
        }
    }

    // Watter
    if (HaveOcean && ContinentAmount > 0)
    {
        while (MaxBoundX * 2 / ContinentAmount < 25)
        {
            ContinentAmount--;
            UE_LOG(LogTemp, Warning, TEXT("MaxBoundX %i ContinentAmount %i"), MaxBoundX * 2, ContinentAmount)
        }
        int32 StartPoint = 0;
        int32 OffsetStartPoint = 0;
        int32 OceanMedianaAmount = 0;
        FVector2D CurrentIndex = {0, 0};
        ACCItemHexagonActor *CurrentItem, *NarcoalCurrentItem = nullptr;
        UMaterialInstanceDynamic* TempMaterial = nullptr;
        if (ContinentAmount > 1)
        {
            OceanMedianaAmount = ContinentAmount - 1;
            ////////////////////////

            for (int32 o = 0; o < OceanMedianaAmount; o++)
            {
                if (OceanMedianaAmount % 2 != 0)
                {
                    OffsetStartPoint = (MaxBoundX * 2 / OceanMedianaAmount) / 2;
                    // Cheak first index
                    if (o == 0)
                    {
                        CurrentIndex = {0, 0};
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
                    else
                    {
                        CurrentIndex = {0, 0};
                        CurrentIndex.X += OffsetStartPoint+(OffsetStartPoint*o);
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
                        CurrentIndex.X += OffsetStartPoint + (OffsetStartPoint * o);
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
                        CurrentIndex = {0, 0};
                        CurrentIndex.X -= OffsetStartPoint + (OffsetStartPoint * o);
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
                        CurrentIndex.X -= OffsetStartPoint + (OffsetStartPoint * o);
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
                }
                else
                {
                    OffsetStartPoint = (MaxBoundX * 2 / OceanMedianaAmount);
                    CurrentIndex = {0, 0};
                    CurrentIndex.X += OffsetStartPoint;
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
                    CurrentIndex.X += OffsetStartPoint;
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
                    OffsetStartPoint = (MaxBoundX * 2 / OceanMedianaAmount) / 2;
                    CurrentIndex = {0, 0};
                    CurrentIndex.X -= OffsetStartPoint;
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
                    CurrentIndex.X -= OffsetStartPoint;
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
            }
        }
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
