#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSpikeActor.generated.h"

UCLASS()
class GODOFROOT_API AFloorSpikeActor : public AActor
{
	GENERATED_BODY()

public:
	AFloorSpikeActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToExplode = 1.0f;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComponent;
	
};
