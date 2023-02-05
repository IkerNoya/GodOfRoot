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
	check(Character->GetPlayerControllerBase());

	AGORPlayerControllerBase* PlayerController = Character->GetPlayerControllerBase();
	if(!PlayerController)
		return;


	const FVector Velocity = Character->GetMovementComponent()->Velocity;
	if(Velocity != FVector::ZeroVector)
	{
		const FVector Direction = Character->GetActorLocation() + Velocity;
		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(), Direction);
		Character->SetActorRotation(FRotator(0,LookRotation.Yaw,0));
	}
	
	AnimInstance->Montage_Play(Montage);
	
	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	Character->DisableInput(PlayerController);

	PlayerController->bIsDodging = true;

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
	
	AGORPlayerControllerBase* PlayerController = Character->GetPlayerControllerBase();
	if(!PlayerController)
		return;
		
	Character->GetCharacterMovement()->bOrientRotationToMovement =false;
	Character->EnableInput(PlayerController);
	
	PlayerController->bIsDodging = false;
}

void UDodgeComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	AGORCharacterBase* Character = CastChecked<AGORCharacterBase>(GetOwner());
	check(Character);
	
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	check(AnimInstance);
	
	if(AnimInstance->OnMontageBlendingOut.Contains(this, "OnAnimationEnded"))
	{
		AnimInstance->OnMontageBlendingOut.RemoveDynamic(this, &UDodgeComponent::OnAnimationEnded);
	}
	
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}
