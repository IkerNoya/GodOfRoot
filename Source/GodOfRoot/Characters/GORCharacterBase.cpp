// Fill out your copyright notice in the Description page of Project Settings.


#include "GORCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GodOfRoot/Animation/AGORBaseCharacterAnimInstance.h"
#include "GodOfRoot/Components/CombatComponent.h"
#include "GodOfRoot/Components/DodgeComponent.h"
#include "GodOfRoot/Components/GORHealthComponentBase.h"
#include "GodOfRoot/Controllers/GORPlayerControllerBase.h"


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
	
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	
	PrimaryActorTick.bCanEverTick = true;
}


void AGORCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if(auto* AnimInstance = Cast<UAGORBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstance->Character = this;
	}

	if(HealthComponent)
	{
		HealthComponent->OnDeathDelegate.AddDynamic(this, &AGORCharacterBase::Die);
		HealthComponent->OnDamageReceivedDelegate.AddDynamic(this, &AGORCharacterBase::OnDamageReceived);
	}
}
 
void AGORCharacterBase::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f) && HealthComponent && !HealthComponent->GetIsDead())
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGORCharacterBase::MoveRight(float Value)
{
	if ( (Controller) && (Value != 0.0f) && HealthComponent && !HealthComponent->GetIsDead())
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AGORCharacterBase::Dash()
{
	if(DodgeComponent && !GetPlayerControllerBase()->bIsDodging && HealthComponent && !HealthComponent->GetIsDead())
	{
		DodgeComponent->ActivateDodge(this);
		if(CombatComponent &&  CombatComponent->IsAttacking())
		{
			CombatComponent->CancelCombo();
		}
	}
}

void AGORCharacterBase::Attack()
{
	if(CombatComponent && HealthComponent && !HealthComponent->GetIsDead())
	{
		CombatComponent->Attack(this);
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
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AGORCharacterBase::Attack);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGORCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGORCharacterBase::MoveRight);
}

AGORPlayerControllerBase* AGORCharacterBase::GetPlayerControllerBase()
{
	AGORPlayerControllerBase* PlayerController = nullptr;
	if(auto* CastedPlayerController = Cast<AGORPlayerControllerBase>(GetController()))
	{
		PlayerController = CastedPlayerController;
	}
	return PlayerController;
}

