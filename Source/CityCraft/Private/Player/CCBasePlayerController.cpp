// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CCBasePlayerController.h"
#include "Player/CCBasePlayerPawn.h"

void ACCBasePlayerController::InitPawn(FVector Location)
{
    FActorSpawnParameters SpawnParam;
    FTransform Transform;
    Location.Z += 40;
    Transform.SetLocation(Location);
    auto TempActor = GetWorld()->SpawnActor<ACCBasePlayerPawn>(PlayerPawnClass, Transform, SpawnParam);
    Possess(TempActor);
}

void ACCBasePlayerController::BeginPlay() {}
