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

private:

protected:
	FTimerHandle ResetAttackTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanAttack = true;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AttackMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* HitMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* IdleMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* DeathMontage;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UGORHealthComponentBase* HealthComponent;

	UFUNCTION()
	virtual void OnDamageReceived(AActor* DamageInstigator, UObject* DamageCause);

	UFUNCTION()
	virtual void OnDeath();

	UFUNCTION()
	virtual void OnHealthAdded();

	UFUNCTION(BlueprintCallable)
	virtual void OnAttack(float AttackCooldown);

	virtual void ResetCanAttack();
};
