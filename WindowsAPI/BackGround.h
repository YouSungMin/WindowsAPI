#pragma once
#include "Actor.h"

class BackGround : public Actor
{
public:
	BackGround() = delete;
	BackGround(const wchar_t* InImagePath);
	~BackGround()override{};
	//BackGround(const wchar_t* InImagePath,float InY);

	virtual void OnRender(Gdiplus::Graphics* InGraphics)override;
	virtual void OnTick(float InDeltaTime)override;


private:
	// 배경화면 스크롤 속도
	float ScrollSpeed = 50.0f;

	float Offset = 0.0f;
};

