#pragma once
#include "Actor.h"

class BackGround : public Actor
{
public:
	BackGround() = delete;
	//BackGround(const wchar_t* InImagePath,float InY);
	BackGround(const wchar_t* InImagePath);
	~BackGround()override{};

	virtual void OnRender(Gdiplus::Graphics* InGraphics)override;
	virtual void OnTick(float InDeltaTime)override;


private:
	// ���ȭ�� ��ũ�� �ӵ�
	float ScrollSpeed = 50.0f;

	float Offset = 0.0f;
};

