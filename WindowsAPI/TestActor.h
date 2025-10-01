#pragma once
#include "Actor.h"
class TestActor : public Actor
{
public:
	TestActor();
	virtual ~TestActor();

	virtual void OnRender(Gdiplus::Graphics* InGraphics)override;
private:
	int WindowHeight = 0;
	int WindowWidth = 0;
	int Interval = 50;
	int HalfSize = 0;

	Gdiplus::SolidBrush* YelloBrush = nullptr;
};

