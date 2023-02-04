// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GORPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class GODOFROOT_API AGORPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float LookRotationSpeed = .5f;
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	
};
