// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "SauceEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GODOFROOT_API ASauceEnemy : public AEnemyBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (ClampMin = 0), meta = (ClampMax = 100), EditAnywhere, BlueprintReadWrite, Category="Phases")
	TArray<float> HealthPhasesPercentages;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Phases")
	int ActualPhase = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloorSpikeAttack")
	int CantOfFloorSpikeToSpawn = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloorSpikeAttack")
	float TimeBetweenAttackFloorSpike = 0.25f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloorSpikeAttack")
	float FloorSpikeAttackCooldown = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpikeThrowAttack")
	float CantOfSpikeToThrow = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpikeThrowAttack")
	float TimeBetweenAttackSpikeThrow = 0.33f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpikeThrowAttack")
	float SpikeThrowAttackCooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpikeTackleAttack")
	float SpikeTackleDamage = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpikeTackleAttack")
	float SpikeTackleImpulse = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpikeTackleAttack")
	float SpikeTackleDistance = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpikeTackleAttack")
	float SpikeTacklePreparationTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpikeTackleAttack")
	float SpikeTackleAttackCooldown = 1.7653f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnMiniSaucesAttack")
	float TimeBetweenSpawn = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnMiniSaucesAttack")
	int CantOfMiniSaucesToSpawn = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnMiniSaucesAttack")
	float MiniSaucesAttackCooldown = 1.75f;
	
	virtual void BeginPlay() override;

public:

	virtual void OnDamageReceived(AActor* DamageInstigator, UObject* DamageCause) override;
};

