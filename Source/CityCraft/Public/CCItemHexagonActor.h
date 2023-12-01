// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCGameInstance.h"
#include "CCItemHexagonActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;

UCLASS()
class CITYCRAFT_API ACCItemHexagonActor : public AActor
{
    GENERATED_BODY()

public:
    ACCItemHexagonActor();

    virtual void Tick(float DeltaTime) override;

    void UpdatePosition(int32 X, int32 Y);
    FVector2D GetPosition() const { return Position; }

    void SetHexBiome(EHexBiome HexStatus);
    EHexBiome GetHexBiome() { return HexBiome; }

    UStaticMeshComponent* GetHexMesh() { return HexMesh; }

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    UStaticMeshComponent* MeshLocation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    UStaticMeshComponent* Outline;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    UStaticMeshComponent* SelectedOutMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    USceneComponent* SceneComponent;

    // HexPlayInfo
    FStorageStruct GetHextorage() const { return Hextorage; }
    void SetHextorage(FStorageStruct Data) { Hextorage = Data; }

    FProductivityStruct GetHexProductivity() const { return HexProductivity; }
    void SetHexProductivity(FProductivityStruct Data) { HexProductivity = Data; }

    FText GetNameBiome();
    FText GetFreeStatusBiome() const { return FText::FromString(NameOwnFruction); };

    // Interaction
    virtual void InteractionItem();

    void SetIsSelect(bool Value);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* HexMesh;

    virtual void BeginPlay() override;

private:
    FStorageStruct Hextorage;
    FProductivityStruct HexProductivity;

    UPROPERTY()
    EHexBiome HexBiome = EHexBiome::Clear;

    UPROPERTY()
    FVector2D Position = {0, 0};

    UPROPERTY()
    FString NameOwnFruction = "None";
};
