#include "SpikeThrowActor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GodOfRoot/Characters/GORCharacterBase.h"
#include "GodOfRoot/Components/GORHealthComponentBase.h"


ASpikeThrowActor::ASpikeThrowActor()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ASpikeThrowActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpikeThrowActor::OnOverlapBegin);
}

void ASpikeThrowActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		if(AGORCharacterBase* Player = Cast<AGORCharacterBase>(OtherActor))
		{
			Player->GetHealthComponent()->ApplyDamage(Damage, GetInstigator(), this);
			Destroy();
		}
	}
}


