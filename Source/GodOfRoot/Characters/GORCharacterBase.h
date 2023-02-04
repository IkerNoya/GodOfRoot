// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GORCharacterBase.generated.h"

UCLASS()
class GODOFROOT_API AGORCharacterBase : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom = nullptr;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input") 
	float BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input") 
	float BaseLookUpRate;

public:

	AGORCharacterBase();

protected:

	virtual void BeginPlay() override;
	
	void MoveForward(float Value);
	
	void MoveRight(float Value);
	
	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
	
public:
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
};
