// Fill out your copyright notice in the Description page of Project Settings.


#include "AGORBaseCharacterAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"
#include "GodOfRoot/Characters/GORCharacterBase.h"


void UAGORBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(!Character)
		return;

	bIsFalling = Character->GetMovementComponent()->IsFalling();
	Speed = Character->GetMovementComponent()->Velocity.Size();
	Direction = CalculateDirection(Character->GetMovementComponent()->Velocity, Character->GetActorRotation());
}
