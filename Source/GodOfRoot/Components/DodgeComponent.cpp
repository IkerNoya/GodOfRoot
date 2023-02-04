// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GodOfRoot/Characters/GORCharacterBase.h"
#include "GodOfRoot/Controllers/GORPlayerControllerBase.h"
#include "Kismet/KismetMathLibrary.h"


UDodgeComponent::UDodgeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UDodgeComponent::ActivateDodge(AGORCharacterBase* Character)
{
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	check(AnimInstance);

	UAnimMontage* Montage = DodgeMontages.Num() > 0 ?
		DodgeMontages[FMath::RandRange(0, DodgeMontages.Num() - 1)] : nullptr;
	
	check(Montage);

	const FVector Velocity = Character->GetMovementComponent()->Velocity;
	if(Velocity != FVector::ZeroVector)
	{
		const FVector Direction = Character->GetActorLocation() + Velocity;
		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(), Direction);
		Character->SetActorRotation(FRotator(0,LookRotation.Yaw,0));
	}
	
	AnimInstance->Montage_Play(Montage);
	
	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	Character->DisableInput(Character->GetPlayerController());

	Character->GetPlayerController()->bIsDodging = true;
	
	if(!AnimInstance->OnMontageBlendingOut.Contains(this, "OnAnimationEnded"))
	{
		AnimInstance->OnMontageBlendingOut.AddDynamic(this, &UDodgeComponent::OnAnimationEnded);
	}
}

void UDodgeComponent::OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	AGORCharacterBase* Character = CastChecked<AGORCharacterBase>(GetOwner());
	check(Character);
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	check(AnimInstance);

	Character->GetCharacterMovement()->bOrientRotationToMovement =false;
	Character->EnableInput(Character->GetPlayerController());
	
	Character->GetPlayerController()->bIsDodging = false;
	
	if(AnimInstance->OnMontageBlendingOut.Contains(this, "OnAnimationEnded"))
	{
		AnimInstance->OnMontageBlendingOut.RemoveDynamic(this, &UDodgeComponent::OnAnimationEnded);
	}
}
