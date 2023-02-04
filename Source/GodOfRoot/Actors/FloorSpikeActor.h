#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSpikeActor.generated.h"

UCLASS()
class GODOFROOT_API AFloorSpikeActor : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:
	AFloorSpikeActor();


private:
	void StartToExplode();

	void FinishExplosion();
	
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToExplode = 1.0f;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		 	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
