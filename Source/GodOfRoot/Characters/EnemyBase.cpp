#include "EnemyBase.h"

#include "GodOfRoot/Components/GORHealthComponentBase.h"


AEnemyBase::AEnemyBase()
{
	HealthComponent = CreateDefaultSubobject<UGORHealthComponentBase>(TEXT("HealthComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDamageReceivedDelegate.AddDynamic(this, &AEnemyBase::OnDamageReceived);
	HealthComponent->OnDeathDelegate.AddDynamic(this, &AEnemyBase::OnDeath);
	HealthComponent->OnHealthAddedDelegate.AddDynamic(this,&AEnemyBase::OnHealthAdded);
	
}

void AEnemyBase::OnDamageReceived(AActor* DamageInstigator, UObject* DamageCause)
{
	//...
}

void AEnemyBase::OnDeath()
{
	bCanAttack = false;
	ResetAttackTimerHandle.Invalidate();
	
	SetLifeSpan(1.0f);
}

void AEnemyBase::OnHealthAdded()
{
	//...
}

void AEnemyBase::OnAttack(float AttackCooldown)
{
	bCanAttack = false;
	
	GetWorld()->GetTimerManager().SetTimer(ResetAttackTimerHandle, this, &AEnemyBase::ResetCanAttack, AttackCooldown, false);
}

void AEnemyBase::ResetCanAttack()
{
	bCanAttack = true;
}

