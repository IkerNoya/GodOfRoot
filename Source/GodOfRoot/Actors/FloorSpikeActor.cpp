#include "FloorSpikeActor.h"

#include "Components/SphereComponent.h"

AFloorSpikeActor::AFloorSpikeActor()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


