#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class GODOFROOT_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

private:

protected:
	virtual void BeginPlay() override;
	
public:
	AEnemyBase();

	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle ResetAttackTimerHandle;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanAttack = true;
	
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

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UGORHealthComponentBase* HealthComponent;

	UFUNCTION()
	void OnDamageReceived(AActor* DamageInstigator, UObject* DamageCause);

	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void OnHealthAdded();

	UFUNCTION(BlueprintCallable)
	void OnAttack(float AttackCooldown);

	void ResetCanAttack();
};
