#include "TestActor.h"
#include "GameManager.h"

TestActor::TestActor()
    :Actor(nullptr)
{
    WindowWidth = GameManager::ScreenWidth;
    WindowHeight = GameManager::ScreenHeight;

    Size = 5;
    HalfSize = Size/2;

    YelloBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255, 0));
}

TestActor::~TestActor()
{
    delete YelloBrush;
    YelloBrush = nullptr;
}

void TestActor::OnRender(Gdiplus::Graphics* InGraphics)
{
    if(!InGraphics || !YelloBrush) return;

    for (int y = 0; y <= WindowHeight; y += Interval)
    {
        for (int x = 0; x <= WindowWidth; x += Interval)
        {
            InGraphics->FillRectangle(YelloBrush, x-HalfSize, y-HalfSize, Size, Size);
        }
    }
}
