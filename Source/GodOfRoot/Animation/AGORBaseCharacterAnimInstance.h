// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AGORBaseCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GODOFROOT_API UAGORBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	class AGORCharacterBase* Character;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool bIsFalling = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float Direction;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
