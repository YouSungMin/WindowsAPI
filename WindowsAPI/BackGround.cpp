#include "BackGround.h"
#include "GameManager.h"

//BackGround::BackGround(const wchar_t* InImagePath, float InY)
BackGround::BackGround(ResourceID InID)
    : Actor(InID)
{
    Pivot.X = 0;
    Pivot.Y = 0;
    //Position.Y = InY;
}

void BackGround::OnRender(Gdiplus::Graphics* InGraphics)
{
    //if (Image)
    //{
    //    // g_PlayerImage가 로딩되어 있다.
    //    if(Position.Y >= g_ScreenSize.Y)
    //        Position.Y = -(g_ScreenSize.Y);
    //    InGraphics->DrawImage(
    //        Image,          // 그려질 이미지
    //        static_cast<int>(Position.X),
    //        static_cast<int>(Position.Y+=Speed),    // 그려질 위치
    //        g_ScreenSize.X,g_ScreenSize.Y);  // 그려질 사이즈
    //}
    if (Image)
    {
        constexpr int PixelGap = 3;
        // Image가 로딩되어 있다.
        int NewY = static_cast<int>(Position.Y - Size * Pivot.Y + Offset);
        if (Offset > GameManager::ScreenHeight)
        {
            Offset = -static_cast<float>(Size);
        }

        int WidthCount = GameManager::ScreenWidth / Size + 1;     // +1은 화면 밖까지 타일을 그리기 위해 추가
        int HeightCount = GameManager::ScreenHeight / Size + 2;// +2는 화면 밖까지 타일을 그리기 위해 추가
        int TotalHeight = (Size - PixelGap) * HeightCount;

        for (int y = -1; y < HeightCount; y++)
        {
            for (int x = 0; x < WidthCount; x++)
            {
                int NewX = static_cast<int>(Position.X - Size * Pivot.X + (Size - PixelGap) * x);
                InGraphics->DrawImage(
                    Image,          // 그려질 이미지
                    NewX,           // 그려질 위치
                    NewY,
                    Size, Size);  // 그려질 사이즈
            }
            NewY += (Size - PixelGap);
            if (NewY > TotalHeight)
            {
                NewY -= (TotalHeight + (Size - PixelGap));
            }
        }
    }
}

void BackGround::OnTick(float InDeltaTime)
{
    Offset += ScrollSpeed * InDeltaTime;
}
