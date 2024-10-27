// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasticCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/SpringArmComponent.h"


ABlasticCharacter::ABlasticCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ABlasticCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlasticCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABlasticCharacter::Jump);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ABlasticCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABlasticCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABlasticCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABlasticCharacter::LookUp);
	
	
}

void ABlasticCharacter::MoveForward(float Value)
{
	if(Controller != nullptr && Value != 0.0f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.0f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void ABlasticCharacter::MoveRight(float Value)
{
	if(Controller != nullptr && Value != 0.0f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.0f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void ABlasticCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ABlasticCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ABlasticCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

