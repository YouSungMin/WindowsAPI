#include "BackGround.h"

BackGround::BackGround(const wchar_t* InImagePath, float InY)
{
    Image = new Gdiplus::Bitmap(InImagePath); // �÷��̾� �̹��� �ε�
    Position.Y = InY;

    if (Image->GetLastStatus() != Gdiplus::Ok)
    {
        // ���������� ���� �ε��� �ȉ��.
        delete Image;       // ���������� ��� ����
        Image = nullptr;
        OutputDebugString(L"�÷��̾� �̹��� �ε� ����");
        MessageBox(g_hMainWindow, L"�÷��̾� �̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
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
        // g_PlayerImage�� �ε��Ǿ� �ִ�.
        if(Position.Y >= g_ScreenSize.Y)
            Position.Y = -(g_ScreenSize.Y);
        InGraphics->DrawImage(
            Image,          // �׷��� �̹���
            static_cast<int>(Position.X),
            static_cast<int>(Position.Y+=Speed),       // �׷��� ��ġ
            g_ScreenSize.X,g_ScreenSize.Y);  // �׷��� ������
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
