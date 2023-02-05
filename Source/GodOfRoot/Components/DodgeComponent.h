// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DodgeComponent.generated.h"


class AGORCharacterBase;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GODOFROOT_API UDodgeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TArray<UAnimMontage*> DodgeMontages;
	
public:
	UDodgeComponent();

	void ActivateDodge(AGORCharacterBase* Character);

protected:
	
	UFUNCTION()
	void OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted);

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
};
