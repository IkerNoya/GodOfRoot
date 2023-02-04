// Fill out your copyright notice in the Description page of Project Settings.


#include "GORCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GodOfRoot/Animation/AGORBaseCharacterAnimInstance.h"
#include "GodOfRoot/Components/DodgeComponent.h"
#include "GodOfRoot/Components/GORHealthComponentBase.h"


AGORCharacterBase::AGORCharacterBase()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UGORHealthComponentBase>(TEXT("HealthComponent"));

	DodgeComponent = CreateDefaultSubobject<UDodgeComponent>(TEXT("DodgeComponent"));
	
	PrimaryActorTick.bCanEverTick = true;
}

void AGORCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if(auto* AnimInstance = Cast<UAGORBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstance->Character = this;
	}
}
 
void AGORCharacterBase::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGORCharacterBase::MoveRight(float Value)
{
	if ( (Controller) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AGORCharacterBase::Dash()
{
	if(DodgeComponent && !GetPlayerController()->bIsDodging)
	{
		DodgeComponent->ActivateDodge(this);
	}
}

void AGORCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGORCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AGORCharacterBase::Dash);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGORCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGORCharacterBase::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

