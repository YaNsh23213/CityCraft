// Fill out your copyright notice in the Description page of Project Settings.

#include "Build/CCSpawnPointBuildActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
ACCSpawnPointBuildActor::ACCSpawnPointBuildActor()
{
    BuildMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildMesh"));
    BuildMesh->SetupAttachment(GetRootComponent());
    PrimaryActorTick.bCanEverTick = true;
}

void ACCSpawnPointBuildActor::ClearSpawnPoint()
{
    SetIsEditable(true);
    if (BuildMesh)
    {
        BuildMesh->SetStaticMesh(DefaultMesh);
    }
}

// Called when the game starts or when spawned
void ACCSpawnPointBuildActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACCSpawnPointBuildActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACCSpawnPointBuildActor::SetNewBuildMesh(UStaticMesh* NewMesh)
{
    if (BuildMesh)
    {
        BuildMesh->SetStaticMesh(NewMesh);
    }
}
