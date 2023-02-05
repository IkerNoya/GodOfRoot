// Fill out your copyright notice in the Description page of Project Settings.


#include "SauceEnemy.h"

#include "GodOfRoot/Components/GORHealthComponentBase.h"

void ASauceEnemy::BeginPlay()
{
	AEnemyBase::BeginPlay();

	ActualPhase = 1.0f;
	
	OnAttack(2.0f);
}

void ASauceEnemy::OnDamageReceived(AActor* DamageInstigator, UObject* DamageCause)
{
	if(HealthComponent->GetIsDead())
	{
		return;
	}

	if(HitMontage && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
	{
		GetMesh()->GetAnimInstance()->Montage_Play(HitMontage);
	}
	
	float Percentage = (HealthComponent->GetHealth() / HealthComponent->GetMaxHealth()) * 100.0f;

	ActualPhase = 0;
	
	for (auto HealthPercentage : HealthPhasesPercentages)
	{
		if(Percentage <= HealthPercentage)
		{
			ActualPhase++;
		}
	}
	
}
