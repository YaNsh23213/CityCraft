// Fill out your copyright notice in the Description page of Project Settings.

#include "CCItemHexagonActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

ACCItemHexagonActor::ACCItemHexagonActor()
{

    PrimaryActorTick.bCanEverTick = true;
    HexMesh = CreateDefaultSubobject<UStaticMeshComponent>("HexMesh");
    HexMesh->SetupAttachment(RootComponent);
}

void ACCItemHexagonActor::BeginPlay()
{
    Super::BeginPlay();
    const auto Material = HexMesh->GetMaterial(0);
    UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
    HexMesh->SetMaterial(0, DynamicMaterial);
}

void ACCItemHexagonActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACCItemHexagonActor::UpdatePosition(int32 X, int32 Y)
{
    Position.X = float(X);
    Position.Y = float(Y);
    UE_LOG(LogTemp, Display, TEXT("Position vector Hex actor [%s] on [%s] "), *GetName(), *Position.ToString());
    auto TextRender = FindComponentByClass<UTextRenderComponent>();
    if (TextRender)
    {
        TextRender->SetText(FText::FromString(FString::Printf(TEXT("%0.f %.0f"), Position.X, Position.Y)));
        //HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
    }
}
