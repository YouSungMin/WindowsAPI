#include "BackGround.h"

//BackGround::BackGround(const wchar_t* InImagePath, float InY)
BackGround::BackGround(const wchar_t* InImagePath)
{
    Pivot.X = 0;
    Pivot.Y = 0;

    Image = new Gdiplus::Bitmap(InImagePath); // �÷��̾� �̹��� �ε�
    //Position.Y = InY;

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
    //if (Image)
    //{
    //    // g_PlayerImage�� �ε��Ǿ� �ִ�.
    //    if(Position.Y >= g_ScreenSize.Y)
    //        Position.Y = -(g_ScreenSize.Y);
    //    InGraphics->DrawImage(
    //        Image,          // �׷��� �̹���
    //        static_cast<int>(Position.X),
    //        static_cast<int>(Position.Y+=Speed),    // �׷��� ��ġ
    //        g_ScreenSize.X,g_ScreenSize.Y);  // �׷��� ������
    //}
    if (Image)
    {
        // Image�� �ε��Ǿ� �ִ�.
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
                    Image,          // �׷��� �̹���
                    NewX,           // �׷��� ��ġ
                    NewY,
                    PixelSize, PixelSize);  // �׷��� ������
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
