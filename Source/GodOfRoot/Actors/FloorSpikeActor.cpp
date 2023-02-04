#include "FloorSpikeActor.h"

#include "Components/SphereComponent.h"
#include "GodOfRoot/Characters/GORCharacterBase.h"
#include "GodOfRoot/Components/GORHealthComponentBase.h"

AFloorSpikeActor::AFloorSpikeActor()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFloorSpikeActor::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AFloorSpikeActor::StartToExplode, TimeToExplode, false);
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFloorSpikeActor::OnOverlapBegin);

}

void AFloorSpikeActor::StartToExplode()
{
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AFloorSpikeActor::FinishExplosion, TimeToExplode, false);

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AFloorSpikeActor::FinishExplosion()
{
	Destroy();
}

void AFloorSpikeActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(OtherActor && OtherActor != GetInstigator())
	{
		if(AGORCharacterBase* Player = Cast<AGORCharacterBase>(OtherActor))
		{
			Player->GetHealthComponent()->ApplyDamage(Damage, GetInstigator(), this);
			SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}
