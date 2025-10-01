#include "BackGround.h"
#include "GameManager.h"

//BackGround::BackGround(const wchar_t* InImagePath, float InY)
BackGround::BackGround(const wchar_t* InImagePath)
    : Actor(InImagePath)
{
    Pivot.X = 0;
    Pivot.Y = 0;
    //Position.Y = InY;
}

void BackGround::OnRender(Gdiplus::Graphics* InGraphics)
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
        constexpr int PixelGap = 3;
        // Image�� �ε��Ǿ� �ִ�.
        int NewY = static_cast<int>(Position.Y - Size * Pivot.Y + Offset);
        if (Offset > GameManager::ScreenHeight)
        {
            Offset = -static_cast<float>(Size);
        }

        int WidthCount = GameManager::ScreenWidth / Size + 1;     // +1�� ȭ�� �۱��� Ÿ���� �׸��� ���� �߰�
        int HeightCount = GameManager::ScreenHeight / Size + 2;// +2�� ȭ�� �۱��� Ÿ���� �׸��� ���� �߰�
        int TotalHeight = (Size - PixelGap) * HeightCount;

        for (int y = -1; y < HeightCount; y++)
        {
            for (int x = 0; x < WidthCount; x++)
            {
                int NewX = static_cast<int>(Position.X - Size * Pivot.X + (Size - PixelGap) * x);
                InGraphics->DrawImage(
                    Image,          // �׷��� �̹���
                    NewX,           // �׷��� ��ġ
                    NewY,
                    Size, Size);  // �׷��� ������
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
