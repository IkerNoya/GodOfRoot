#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpikeThrowActor.generated.h"

UCLASS()
class GODOFROOT_API ASpikeThrowActor : public AActor
{
	GENERATED_BODY()

public:
	ASpikeThrowActor();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedMovement;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent;	
	
};
