#pragma once

#include "Common.h"

class BackGround
{
public:
	BackGround() = delete;
	//BackGround(const wchar_t* InImagePath,float InY);
	BackGround(const wchar_t* InImagePath);
	~BackGround();

	void BackGroundRender(Gdiplus::Graphics* InGraphics);

	void Tick(float InDeltaTime);

private:
	static constexpr int PixelSize = 64;

	Gdiplus::Bitmap* Image = nullptr;   // 플레이어가 그려질 종이

	float Speed = 50.0f;

	PointF Position{ 0.0f, 0.0f };

	PointF Pivot = { 0.5f , 0.5f };

	float Offset = 0.0f;
};

