// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCItemHexagonActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class CITYCRAFT_API ACCItemHexagonActor : public AActor
{
    GENERATED_BODY()

public:
    ACCItemHexagonActor();

    virtual void Tick(float DeltaTime) override;

    void UpdatePosition(int32 X, int32 Y);
    FVector2D GetPosition() const { return Position; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* HexMesh;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    FVector2D Position = {0, 0};
};
