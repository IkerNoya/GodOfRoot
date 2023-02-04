#include "EnemyBase.h"

#include "GodOfRoot/Components/GORHealthComponentBase.h"


AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UGORHealthComponentBase>(TEXT("HealthComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

