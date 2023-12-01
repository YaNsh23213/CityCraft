// Fill out your copyright notice in the Description page of Project Settings.

#include "CCItemHexagonActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

ACCItemHexagonActor::ACCItemHexagonActor()
{

    PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
    HexMesh = CreateDefaultSubobject<UStaticMeshComponent>("HexMesh");
    HexMesh->SetupAttachment(RootComponent);
    MeshLocation = CreateDefaultSubobject<UStaticMeshComponent>("MeshMap");
    MeshLocation->SetupAttachment(RootComponent);
    Outline = CreateDefaultSubobject<UStaticMeshComponent>("Outline");
    Outline->SetupAttachment(RootComponent);
    SelectedOutMesh = CreateDefaultSubobject<UStaticMeshComponent>("SelectedOutMesh");
    SelectedOutMesh->SetupAttachment(RootComponent);
}

FText ACCItemHexagonActor::GetNameBiome()
{
    switch (HexBiome)
    {
        case EHexBiome::Clear: return FText ::FromString(""); break;
        case EHexBiome::Snow: return FText ::FromString("Snow"); break;
        case EHexBiome::Desert: return FText ::FromString("Desert"); break;
        case EHexBiome::Meadow: return FText ::FromString("Meadow"); break;
        case EHexBiome::Ocean: return FText ::FromString("Ocean"); break;
        case EHexBiome::Coast: return FText ::FromString("Coast"); break;
        case EHexBiome::Lake: return FText ::FromString("Lake"); break;
        case EHexBiome::SnowHill: return FText ::FromString("Snow Hill"); break;
        case EHexBiome::DesertHill: return FText ::FromString("Desert Hill"); break;
        case EHexBiome::MeadowHill: return FText ::FromString("Meadow Hill"); break;
        case EHexBiome::SnowHillWood: return FText ::FromString("Snow Hill Wood"); break;
        case EHexBiome::DesertHillWood: return FText ::FromString("Desert Hill Wood"); break;
        case EHexBiome::MeadowHillWood: return FText ::FromString("Meadow Hill Wood"); break;
        case EHexBiome::SnowWood: return FText ::FromString("Snow Wood"); break;
        case EHexBiome::DesertWood: return FText ::FromString("Desert Wood"); break;
        case EHexBiome::MeadowWood: return FText ::FromString("Meadow Wood"); break;
        default: return FText ::FromString(""); break;
    }
    return FText ::FromString("");
}

void ACCItemHexagonActor::InteractionItem()
{
    UE_LOG(LogTemp, Warning, TEXT("Item interaction"))
}

void ACCItemHexagonActor::BeginPlay()
{
    Super::BeginPlay();
    const auto Material = HexMesh->GetMaterial(0);
    UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
    HexMesh->SetMaterial(0, DynamicMaterial);
    // const auto MaterialOut = SelectedMesh->GetMaterial(0);
    // UMaterialInstanceDynamic* DynamicMaterialOut = UMaterialInstanceDynamic::Create(MaterialOut, this);
    // SelectedMesh->SetMaterial(0, DynamicMaterialOut);
}
void ACCItemHexagonActor::SetIsSelect(bool Value)
{
    Value ? SelectedOutMesh->SetVisibility(true) : SelectedOutMesh->SetVisibility(false);
}
void ACCItemHexagonActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACCItemHexagonActor::UpdatePosition(int32 X, int32 Y)
{
    Position.X = float(X);
    Position.Y = float(Y);
    auto TextRender = FindComponentByClass<UTextRenderComponent>();
    if (TextRender)
    {
        TextRender->SetText(FText::FromString(FString::Printf(TEXT("%0.f %.0f"), Position.X, Position.Y)));
    }
}

void ACCItemHexagonActor::SetHexBiome(EHexBiome HexStatus)
{
    HexBiome = HexStatus;
    FProductivityStruct TempStruct;
    switch (HexStatus)
    {
        case EHexBiome::Clear:
            TempStruct.EatProductivity = 0;
            TempStruct.ProductionProductivity = 0;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::Snow:
            TempStruct.EatProductivity = 1;
            TempStruct.ProductionProductivity = 0;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::Desert:
            TempStruct.EatProductivity = 0;
            TempStruct.ProductionProductivity = 0;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::Meadow:
            TempStruct.EatProductivity = 2;
            TempStruct.ProductionProductivity = 0;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::Ocean:
            TempStruct.EatProductivity = 1;
            TempStruct.ProductionProductivity = 0;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::Coast:
            TempStruct.EatProductivity = 2;
            TempStruct.ProductionProductivity = 0;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::Lake:
            TempStruct.EatProductivity = 1;
            TempStruct.ProductionProductivity = 1;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::SnowHill:
            TempStruct.EatProductivity = 0;
            TempStruct.ProductionProductivity = 1;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::DesertHill:
            TempStruct.EatProductivity = 0;
            TempStruct.ProductionProductivity = 1;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::MeadowHill:
            TempStruct.EatProductivity = 2;
            TempStruct.ProductionProductivity = 1;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::SnowHillWood:
            TempStruct.EatProductivity = 1;
            TempStruct.ProductionProductivity = 2;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::DesertHillWood:
            TempStruct.EatProductivity = 0;
            TempStruct.ProductionProductivity = 2;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::MeadowHillWood:
            TempStruct.EatProductivity = 2;
            TempStruct.ProductionProductivity = 2;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::SnowWood:
            TempStruct.EatProductivity = 0;
            TempStruct.ProductionProductivity = 1;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::DesertWood:
            TempStruct.EatProductivity = 0;
            TempStruct.ProductionProductivity = 1;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        case EHexBiome::MeadowWood:
            TempStruct.EatProductivity = 2;
            TempStruct.ProductionProductivity = 1;
            TempStruct.GoldProductivity = 0;
            SetHexProductivity(TempStruct);
            break;
        default: break;
    }
}
