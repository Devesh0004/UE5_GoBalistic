// Fill out your copyright notice in the Description page of Project Settings.


#include "BalisticHUD.h"

void ABalisticHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D ViewPortSize;
	if(GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
		const FVector2D ViewPortCenter(ViewPortSize.X / 2.f, ViewPortSize.Y / 2.f);

		if(HUDPackage.CrosshairCenter)
		{
			DrawCrosshair(HUDPackage.CrosshairCenter, ViewPortCenter);
		}
		if(HUDPackage.CrosshairLeft)
		{
			DrawCrosshair(HUDPackage.CrosshairLeft, ViewPortCenter);
		}
		if(HUDPackage.CrosshairRight)
		{
			DrawCrosshair(HUDPackage.CrosshairRight, ViewPortCenter);
		}
		if(HUDPackage.CrosshairTop)
		{
			DrawCrosshair(HUDPackage.CrosshairTop, ViewPortCenter);
		}
		if(HUDPackage.CrosshairBottom)
		{
			DrawCrosshair(HUDPackage.CrosshairBottom, ViewPortCenter);
		}
	}
}

void ABalisticHUD::DrawCrosshair(UTexture2D* Texture, FVector2D ViewPortCenter)
{
	const float TextureWidth = Texture->GetSizeX();
	const float TextureHeight = Texture->GetSizeY();
	const FVector2D TextureDrawPoint(ViewPortCenter.X - (TextureWidth / 2.f), ViewPortCenter.Y - (TextureHeight / 2.f));

	DrawTexture(
		Texture,
		TextureDrawPoint.X,
		TextureDrawPoint.Y,
		TextureWidth,
		TextureHeight,
		0.f, 0.f,
		1.f, 1.f,
		FLinearColor::White);
}
