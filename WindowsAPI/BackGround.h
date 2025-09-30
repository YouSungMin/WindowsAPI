#pragma once

#include <Windows.h>
#include <gdiplus.h>

extern HWND g_hMainWindow;
extern Gdiplus::Point g_ScreenSize;
using PointF = Gdiplus::PointF;

class BackGround
{
public:
	BackGround() = delete;
	BackGround(const wchar_t* InImagePath,float InY);
	~BackGround();

	void BackGroundRender(Gdiplus::Graphics* InGraphics);
private:
	Gdiplus::Bitmap* Image = nullptr;   // 플레이어가 그려질 종이
	float Speed = 5.0f;
	PointF Position{ 0.0f, 0.0f };
};

