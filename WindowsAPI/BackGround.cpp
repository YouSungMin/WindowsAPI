#include "BackGround.h"

BackGround::BackGround(const wchar_t* InImagePath, float InY)
{
    Image = new Gdiplus::Bitmap(InImagePath); // 플레이어 이미지 로딩
    Position.Y = InY;

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
    if (Image)
    {
        // g_PlayerImage가 로딩되어 있다.
        if(Position.Y >= g_ScreenSize.Y)
            Position.Y = -(g_ScreenSize.Y);
        InGraphics->DrawImage(
            Image,          // 그려질 이미지
            static_cast<int>(Position.X),
            static_cast<int>(Position.Y+=Speed),       // 그려질 위치
            g_ScreenSize.X,g_ScreenSize.Y);  // 그려질 사이즈
    }
    else
    {
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,
            100, 100,
            100, 100);
    }
}
