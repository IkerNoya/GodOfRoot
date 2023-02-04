// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GodOfRoot/Controllers/GORPlayerControllerBase.h"
#include "GORCharacterBase.generated.h"

class UDodgeComponent;
class UGORHealthComponentBase;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UGORHealthComponentBase* HealthComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UDodgeComponent* DodgeComponent = nullptr;


public:

	AGORCharacterBase();

protected:

	virtual void BeginPlay() override;
	
	void MoveForward(float Value);
	
	void MoveRight(float Value);

	void Dash();
	
public:
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE UGORHealthComponentBase* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE class AGORPlayerControllerBase* GetPlayerController() {return CastChecked<AGORPlayerControllerBase>(GetController());}
};
