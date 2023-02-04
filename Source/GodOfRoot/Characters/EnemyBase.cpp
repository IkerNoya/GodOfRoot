#include "EnemyBase.h"

#include "GodOfRoot/Components/GORHealthComponentBase.h"


AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UGORHealthComponentBase>(TEXT("HealthComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDamageReceivedDelegate.AddDynamic(this, &AEnemyBase::OnDamageReceived);
	HealthComponent->OnDeathDelegate.AddDynamic(this, &AEnemyBase::OnDeath);
	HealthComponent->OnHealthAddedDelegate.AddDynamic(this,&AEnemyBase::OnHealthAdded);

	OnAttack(2.0f);
	
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::OnDamageReceived(AActor* DamageInstigator, UObject* DamageCause)
{
	//...
}

void AEnemyBase::OnDeath()
{
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

