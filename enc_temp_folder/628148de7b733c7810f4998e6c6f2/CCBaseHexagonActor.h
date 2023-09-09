// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCBaseHexagonActor.generated.h"

class ACCItemHexagonActor;

UCLASS()
class CITYCRAFT_API ACCBaseHexagonActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ACCBaseHexagonActor();

	virtual void Tick(float DeltaTime) override;

	void InitMap(int32 Offset);

protected:

	//Base hexagon item
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    TSubclassOf<ACCItemHexagonActor> HexClass;

	virtual void BeginPlay() override;

	private:

};
