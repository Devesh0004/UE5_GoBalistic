// Fill out your copyright notice in the Description page of Project Settings.


#include "BalisticAnimInstance.h"

#include "BlasticCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GoBalistic/Weapon/Weapon.h"
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
	EquippedWeapon = BlasticCharacter->GetEquippedWeapomn();
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

	AO_Yaw = BlasticCharacter->GetAO_Yaw();
	AO_Pitch = BlasticCharacter->GetAO_Pitch();

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && BlasticCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		BlasticCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));
	}
}
