// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCSpawnPointBuildActor.generated.h"

UCLASS()
class CITYCRAFT_API ACCSpawnPointBuildActor : public AActor
{
    GENERATED_BODY()

public:
    ACCSpawnPointBuildActor();

    virtual void Tick(float DeltaTime) override;

    void SetNewBuildMesh(UStaticMesh* NewMesh);

    bool GetIsEditable() const { return IsCanBeEditable; }
    void SetIsEditable(bool NewVariable) { IsCanBeEditable = NewVariable; }

    void ClearSpawnPoint();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    UStaticMeshComponent* BuildMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    UStaticMesh* DefaultMesh;

    UPROPERTY()
    bool IsCanBeEditable = true;
};
