// Fill out your copyright notice in the Description page of Project Settings.


#include "BalisticAnimInstance.h"

#include "BlasticCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBalisticAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BlasticCharacter = Cast<ABlasticCharacter>(TryGetPawnOwner());
}

void UBalisticAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (BlasticCharacter == nullptr)
	{
		BlasticCharacter = Cast<ABlasticCharacter>(TryGetPawnOwner());
	}

	if (BlasticCharacter == nullptr) return;

	FVector Velocity = BlasticCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = BlasticCharacter->GetCharacterMovement()->IsFalling();
	bIsAcceleratring = BlasticCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	bWeaponEquipped = BlasticCharacter->IsWeaponEquipped();
	bIsCrouched = BlasticCharacter->bIsCrouched;
	bAiming = BlasticCharacter->IsAiming();

	FRotator AimRotation = BlasticCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(BlasticCharacter->GetVelocity());	
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f);
	YawOffset = DeltaRotation.Yaw;

	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = BlasticCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);
}
