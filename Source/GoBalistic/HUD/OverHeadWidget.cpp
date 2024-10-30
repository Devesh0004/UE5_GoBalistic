// Fill out your copyright notice in the Description page of Project Settings.


#include "OverHeadWidget.h"

#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverHeadWidget::SetDisplayText(FString TextToDisplay)
{
	if(DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverHeadWidget::ShowPLayerNetRole(APawn* InPawn)
{
	ENetRole LocalRole = InPawn->GetLocalRole();
	FString Role;

	switch (LocalRole)
	{
	case ROLE_Authority:
		Role = FString("Authority");
		break;

	case ROLE_AutonomousProxy:
		Role = FString("AutonomousProxy");
		break;

	case ROLE_SimulatedProxy:
		Role = FString("SimulatedProxy");
		break;

	case ROLE_None:
		Role = FString("None");
		break;
	}

	FString PlayerName = InPawn->GetName();
	FString LocalRoleString = FString::Printf(TEXT("PlayerName: %s, Local Role: %s"),*PlayerName, *Role);
	SetDisplayText(LocalRoleString);
}

void UOverHeadWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	RemoveFromParent();
}
