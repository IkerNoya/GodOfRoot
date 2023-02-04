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

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 25.0f;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComponent;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
