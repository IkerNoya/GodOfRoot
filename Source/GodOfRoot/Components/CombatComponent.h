// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GodOfRoot/Animation/AGORBaseCharacterAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CombatComponent.generated.h"

USTRUCT(BlueprintType)
struct FAttackData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* Montage = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Damage = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float TimeBetweenHits;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray<USoundBase*> HitSound;
};

USTRUCT(BlueprintType)
struct FComboData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray<FAttackData> Combo;

	int32 AttackIndex = 0;

};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GODOFROOT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
	
	FTimerHandle TimeBetweenHitsHandle;

	bool bIsAttacking = false;

	float CurrentDamage = 0;
	
	int32 CurrentAttackIndex = 0;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray<FComboData> Combos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	FComboData CurrentCombo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float TraceDistance = 50.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float TraceRadius = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TEnumAsByte<EDrawDebugTrace::Type> DrawType;

	UPROPERTY()
	TArray<AActor*> EnemiesHit;

	
public:
	UPROPERTY(BlueprintReadWrite)
	bool bCanAttack = true;

protected:
	virtual void BeginPlay() override;
	
public:
	UCombatComponent();
	
	UFUNCTION(BlueprintCallable)
	void CheckHit();
	UFUNCTION(BlueprintCallable)
	void EndHit();

	UFUNCTION(BlueprintCallable)
	void Attack(AGORCharacterBase* Character);

	UFUNCTION(BlueprintCallable)
	void CancelAttack();

	UFUNCTION()
	void MontageFinished(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void CancelCombo();

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsAttacking() const {return bIsAttacking;}
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool CanAttack() const {return bCanAttack;}
	
};
