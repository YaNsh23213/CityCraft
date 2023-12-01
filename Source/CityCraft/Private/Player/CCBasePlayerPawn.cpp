// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CCBasePlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CCItemHexagonActor.h"
#include "CCGameInstance.h"
#include "UI/CCBasePlayerWidget.h"

ACCBasePlayerPawn::ACCBasePlayerPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp3P"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ACCBasePlayerPawn::BeginPlay()
{
    Super::BeginPlay();
    const auto PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = true;
    }
    BasePlayerWidget = CreateWidget<UCCBasePlayerWidget>(GetWorld(), BasePlayerWidgetClass);
    BasePlayerWidget->ChangeHex();
}

// Called every frame
void ACCBasePlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACCBasePlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("UpDown", this, &ACCBasePlayerPawn::MoveUpDown);
    PlayerInputComponent->BindAxis("LeftRight", this, &ACCBasePlayerPawn::MoveLeftRight);

    PlayerInputComponent->BindAction("LeftMouseAction", IE_Pressed, this, &ACCBasePlayerPawn::LeftMouseClick);
}

void ACCBasePlayerPawn::MoveUpDown(float Value)
{
    if (Value == 0) return;
    auto Location = GetActorLocation();
    Location.X += Value * Sensitive;
    SetActorLocation(Location);
}

void ACCBasePlayerPawn::MoveLeftRight(float Value)
{
    if (Value == 0) return;
    auto Location = GetActorLocation();
    Location.Y += Value * Sensitive;
    SetActorLocation(Location);
}

void ACCBasePlayerPawn::LeftMouseClick()
{
    BasePlayerWidget->RemoveFromParent();
    BasePlayerWidget->ChangeHex();
    FVector WorldPosition;
    FVector WorldDirection;
    FHitResult HitResult;
    FVector2D ScreenPosition;

    const auto PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        PlayerController->GetMousePosition(ScreenPosition.X, ScreenPosition.Y);
        PlayerController->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldPosition, WorldDirection);
        FVector TraceStart = WorldPosition;
        FVector TraceEnd = WorldPosition + (WorldDirection * 200000);
        auto TargetSpawn = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
        if (HitResult.bBlockingHit && HitResult.GetActor())
        {
            if (CurrentSelected)
            {
                CurrentSelected->SetIsSelect(false);
            }
            CurrentSelected = Cast<ACCItemHexagonActor>(HitResult.GetActor());
            if (CurrentSelected)
            {
                CurrentSelected->InteractionItem();
                CurrentSelected->SetIsSelect(true);
                UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *GetEnumAsString(CurrentSelected->GetHexBiome()).ToString());
                UpdateWidgetInfoFromHexInfo(CurrentSelected->GetHextorage(), CurrentSelected->GetHexProductivity(),
                    CurrentSelected->GetNameBiome(), CurrentSelected->GetFreeStatusBiome(), nullptr);
                BasePlayerWidget->AddToViewport();
            }
        }
    }
}

FText ACCBasePlayerPawn::GetEnumAsString(EHexBiome EnumValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EHexBiome"), true);
    if (!EnumPtr) return NSLOCTEXT("Invalid", "Invalid", "Invalid");
    return EnumPtr->GetDisplayValueAsText(EnumValue);
}

void ACCBasePlayerPawn::UpdateWidgetInfoFromHexInfo(
    FStorageStruct DataS, FProductivityStruct DataP, FText NameHex, FText IsFree, UTexture2D* NewImage)
{
    if (DataP.EatProductivity != 0)
    {
        BasePlayerWidget->UpdateStatusEat(true, DataP.EatProductivity);
    }
    if (DataP.ProductionProductivity != 0)
    {
        BasePlayerWidget->UpdateStatusProduction(true, DataP.ProductionProductivity);
    }
    if (DataP.GoldProductivity != 0)
    {
        BasePlayerWidget->UpdateStatusGold(true, DataP.GoldProductivity);
    }

    if (DataS.EatStorage != 0)
    {
        BasePlayerWidget->UpdateStatusEatStorage(true, DataS.EatStorage);
    }
    if (DataS.ProductionStorage != 0)
    {
        BasePlayerWidget->UpdateStatusProductionStorage(true, DataS.ProductionStorage);
    }
    if (DataS.GoldStorage != 0)
    {
        BasePlayerWidget->UpdateStatusGoldStorage(true, DataS.GoldStorage);
    }
    BasePlayerWidget->UpdateMainInfo(NewImage, NameHex, IsFree);
}
