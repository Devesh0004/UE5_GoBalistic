// Fill out your copyright notice in the Description page of Project Settings.


#include "BalisticAnimInstance.h"

#include "BlasticCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}
