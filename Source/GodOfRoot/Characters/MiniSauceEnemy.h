// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "MiniSauceEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GODOFROOT_API AMiniSauceEnemy : public AEnemyBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack");
	float Damage = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float AttackRange = 300.0f;
	
};
