// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "GORHealthComponentBase.h"
#include "GameFramework/Character.h"
#include "GodOfRoot/Characters/EnemyBase.h"
#include "GodOfRoot/Characters/GORCharacterBase.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCombatComponent::CheckHit()
{
	FVector TraceLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * TraceDistance;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	for(AActor* Enemy : EnemiesHit)
	{
		if(Enemy)
		{
			ActorsToIgnore.Add(Enemy);
		}
	}
	FHitResult HitResult;
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), TraceLocation, TraceLocation, TraceRadius, ObjectTypes, false, ActorsToIgnore, DrawType, HitResult, true);
	if(HitResult.bBlockingHit)
	{
		if(AEnemyBase* Enemy = Cast<AEnemyBase>(HitResult.Actor))
		{
			UGORHealthComponentBase* HealthComponent = CastChecked<UGORHealthComponentBase>(Enemy->GetComponentByClass(UGORHealthComponentBase::StaticClass()));
			HealthComponent->ApplyDamage(CurrentDamage, GetOwner(), nullptr);
			EnemiesHit.Add(Enemy);
		}
	}
}

void UCombatComponent::EndHit()
{
	EnemiesHit.Empty();
}

void UCombatComponent::Attack(AGORCharacterBase* Character)
{
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if(!CanAttack()) return;
	
	if(CurrentCombo.Combo.Num() <= 0)
	{
		CurrentCombo = Combos[0];
		CurrentCombo.AttackIndex = 0;
		AnimInstance->Montage_Play(CurrentCombo.Combo[CurrentCombo.AttackIndex].Montage);
		AnimInstance->OnMontageBlendingOut.AddDynamic(this, &UCombatComponent::MontageFinished);
		CurrentCombo.AttackIndex++;
		CurrentDamage = CurrentCombo.Combo[CurrentCombo.AttackIndex].Damage;
		bCanAttack = false;
		UE_LOG(LogTemp, Warning, TEXT("HOLA"))
	}
	else
	{
		if(CurrentCombo.AttackIndex >= CurrentCombo.Combo.Num())
		{
			CancelCombo();
			CurrentCombo.AttackIndex = 0;
			GetWorld()->GetTimerManager().ClearTimer(TimeBetweenHitsHandle);
			Attack(Character);
		}
		else
		{
			AnimInstance->Montage_Play(CurrentCombo.Combo[CurrentCombo.AttackIndex].Montage);
			AnimInstance->OnMontageBlendingOut.AddDynamic(this, &UCombatComponent::MontageFinished);
			CurrentDamage = CurrentCombo.Combo[CurrentCombo.AttackIndex].Damage;
			CurrentCombo.AttackIndex++;
			bCanAttack = false;
		}
	}
}

void UCombatComponent::CancelAttack()
{
	CancelCombo();
}

void UCombatComponent::MontageFinished(UAnimMontage* Montage, bool bInterrupted)
{
	bCanAttack=true;
	if(CurrentCombo.Combo.Num()>0)
	{
		GetWorld()->GetTimerManager().SetTimer(TimeBetweenHitsHandle, this, &UCombatComponent::CancelCombo, CurrentCombo.Combo[CurrentCombo.AttackIndex].TimeBetweenHits, false);
	}
}

void UCombatComponent::CancelCombo()
{
	CurrentCombo = FComboData();
	bIsAttacking = false;
	bCanAttack = true;
}



