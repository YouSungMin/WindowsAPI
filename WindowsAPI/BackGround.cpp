#include "BackGround.h"

//BackGround::BackGround(const wchar_t* InImagePath, float InY)
BackGround::BackGround(const wchar_t* InImagePath)
{
    Pivot.X = 0;
    Pivot.Y = 0;

    Image = new Gdiplus::Bitmap(InImagePath); // 플레이어 이미지 로딩
    //Position.Y = InY;

    if (Image->GetLastStatus() != Gdiplus::Ok)
    {
        // 정상적으로 파일 로딩이 안됬다.
        delete Image;       // 실패했으면 즉시 해제
        Image = nullptr;
        OutputDebugString(L"플레이어 이미지 로드 실패");
        MessageBox(g_hMainWindow, L"플레이어 이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
    }
}

BackGround::~BackGround()
{
    if (Image)
    {
        delete Image;
        Image = nullptr;
    }
}

void BackGround::BackGroundRender(Gdiplus::Graphics* InGraphics)
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
        // Image가 로딩되어 있다.
        int NewY = static_cast<int>(Position.Y - PixelSize * Pivot.Y + Offset);
        if (Offset > g_ScreenSize.Y)
        {
            Offset = -PixelSize;
        }

        int WidthCount = g_ScreenSize.X / PixelSize + 1;
        int HeightCount = g_ScreenSize.Y / PixelSize + 2;
        int TotalHeight = (PixelSize - 3) * HeightCount;

        for (int y = -1; y < HeightCount; y++)
        {
            for (int x = 0; x < WidthCount; x++)
            {
                int NewX = static_cast<int>(Position.X - PixelSize * Pivot.X + (PixelSize - 3) * x);
                InGraphics->DrawImage(
                    Image,          // 그려질 이미지
                    NewX,           // 그려질 위치
                    NewY,
                    PixelSize, PixelSize);  // 그려질 사이즈
            }
            NewY += (PixelSize - 3);
            if (NewY > TotalHeight)
            {
                NewY -= (TotalHeight + (PixelSize - 3));
            }
        }
    }
}

void BackGround::Tick(float InDeltaTime)
{
    Offset += Speed * InDeltaTime;
}
