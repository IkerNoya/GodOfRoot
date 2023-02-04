#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class GODOFROOT_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

private:

protected:
	virtual void BeginPlay() override;
	
public:
	AEnemyBase();

	virtual void Tick(float DeltaTime) override;

private:
	
protected:

public:

	UPROPERTY(EditAnywhere)
	class UGORHealthComponentBase* HealthComponent;
	
};
