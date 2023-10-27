// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CCMainGameMode.h"
#include "CCBaseHexagonActor.h"
#include "CCItemHexagonActor.h"
#include "Player/CCBasePlayerController.h"

void ACCMainGameMode::BeginPlay()
{
    FActorSpawnParameters SpawnParam;
    FTransform Transform;
    Transform.SetLocation({0, 0, 0});
    GetWorld()->SpawnActor<ACCBaseHexagonActor>(GenerationActorClass, Transform, SpawnParam);
}

void ACCMainGameMode::AfterGeneration(ACCBaseHexagonActor* GenetationActor)
{
    auto ArrayHex = GenetationActor->GetHexArray();
    FActorSpawnParameters SpawnParam;
    FVector2D SpawnIndex;
    FVector SpawnPosition;
    if (ArrayHex.Num() > 0)
    {
        for (int32 i = 0; i < ArrayHex.Num() - 1; i++)
        {
            int32 Result = FMath::RandRange(0, ArrayHex.Num() - 1);
            if (ArrayHex[Result]->GetHexBiome() != EHexBiome::Lake)
            {
                SpawnIndex = ArrayHex[Result]->GetPosition();
                SpawnPosition = ArrayHex[Result]->GetActorLocation();
                break;
            }
        }
        FTransform Transform;
        Transform.SetLocation(SpawnPosition);
        auto TempController = Cast<ACCBasePlayerController>(GetWorld()->GetFirstPlayerController());
        if (TempController)
        {
            TempController->InitPawn(SpawnPosition);
        }
    }
}
