// Fill out your copyright notice in the Description page of Project Settings.


#include "GORPlayerControllerBase.h"

#include "Kismet/KismetMathLibrary.h"

void AGORPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode = FInputModeGameOnly();
	InputMode.SetConsumeCaptureMouseDown(false);
	SetInputMode(InputMode);
	SetShowMouseCursor(true);
}

void AGORPlayerControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(bIsDodging)
		return;
	
	const FVector PawnLocation = GetPawn()->GetActorLocation();
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, true, HitResult);
	FRotator LookRotation;
	
	// if(HitResult.ImpactPoint == FVector.)
	// {
		LookRotation = UKismetMathLibrary::FindLookAtRotation(PawnLocation, HitResult.ImpactPoint);
	// }
	// else
	// {
	// 	const FVector PlayerDirection = GetPawn()->GetVelocity() + PawnLocation;
	// 	LookRotation = UKismetMathLibrary::FindLookAtRotation(PawnLocation, PlayerDirection);
	// }
	GetPawn()->SetActorRotation(FMath::RInterpTo(GetPawn()->GetActorRotation(), FRotator(0,LookRotation.Yaw,0), DeltaSeconds, LookRotationSpeed));
}
	