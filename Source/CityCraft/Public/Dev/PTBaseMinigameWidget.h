// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PTBaseMinigameWidget.generated.h"

UCLASS()
class CITYCRAFT_API UPTBaseMinigameWidget : public UUserWidget
{
    GENERATED_BODY()
public:

protected:
    virtual void NativeConstruct() override;

private:
  
};
