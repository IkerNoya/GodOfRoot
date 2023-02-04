// Fill out your copyright notice in the Description page of Project Settings.


#include "GORPlayerControllerBase.h"

#include "Kismet/KismetMathLibrary.h"

void AGORPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameAndUI InputMode = FInputModeGameAndUI();
	SetInputMode(InputMode);
	SetShowMouseCursor(true);
}

void AGORPlayerControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const FVector PawnLocation = GetPawn()->GetActorLocation();
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, true, HitResult);
	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(PawnLocation, HitResult.ImpactPoint);
	GetPawn()->SetActorRotation(FMath::RInterpTo(GetPawn()->GetActorRotation(), FRotator(0,LookRotation.Yaw,0), DeltaSeconds, LookRotationSpeed));
}
	