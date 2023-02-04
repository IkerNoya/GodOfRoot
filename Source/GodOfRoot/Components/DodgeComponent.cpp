// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GodOfRoot/Characters/GORCharacterBase.h"
#include "GodOfRoot/Controllers/GORPlayerControllerBase.h"


UDodgeComponent::UDodgeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UDodgeComponent::ActivateDodge(AGORCharacterBase* Character)
{
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	check(AnimInstance);

	UAnimMontage* Montage = DodgeMontages[FMath::RandRange(0, DodgeMontages.Num() - 1)];
	AnimInstance->Montage_Play(Montage);

	AGORPlayerControllerBase* Controller = CastChecked<AGORPlayerControllerBase>(Character);
	check(Controller);
	
	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	Character->DisableInput(Controller);

	Controller->bIsDodging = true;
	
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
	AGORPlayerControllerBase* Controller = CastChecked<AGORPlayerControllerBase>(Character);
	check(Controller);

	Character->GetCharacterMovement()->bOrientRotationToMovement =false;
	Character->EnableInput(Controller);
	
	Controller->bIsDodging = false;
	
	if(AnimInstance->OnMontageBlendingOut.Contains(this, "OnAnimationEnded"))
	{
		AnimInstance->OnMontageBlendingOut.RemoveDynamic(this, &UDodgeComponent::OnAnimationEnded);
	}
}
