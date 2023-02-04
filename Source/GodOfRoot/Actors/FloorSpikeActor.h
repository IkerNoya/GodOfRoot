#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "FloorSpikeActor.generated.h"

UCLASS()
class GODOFROOT_API AFloorSpikeActor : public AActor
{
	GENERATED_BODY()

public:
	AFloorSpikeActor();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent;	
};
