// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GORHealthComponentBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageReceivedSignature, AActor*, DamageInstigator, UObject*, DamageCause);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthAddedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GODOFROOT_API UGORHealthComponentBase : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UGORHealthComponentBase();

private:

protected:
	UPROPERTY(EditAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	bool bIsDead = false;

	UPROPERTY(EditAnywhere)
	bool bCanReceiveDamage = true;
	
public:


	UFUNCTION(BlueprintCallable)
	bool ApplyDamage(float Damage, AActor* DamageInstigator, UObject* DamageCause);

	void AddHealth(float ExtraHealth);

	UPROPERTY(BlueprintAssignable)
	FOnDamageReceivedSignature OnDamageReceivedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeathDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHealthAddedSignature OnHealthAddedDelegate;

	inline float GetHealth() const {return Health; }
	inline float GetMaxHealth() const { return MaxHealth; }

	inline bool GetIsDead() const { return bIsDead; }

	inline bool GetCanReceiveDamage() const { return bCanReceiveDamage; }

	void SetCanReceiveDamage(bool Val);
	
};
