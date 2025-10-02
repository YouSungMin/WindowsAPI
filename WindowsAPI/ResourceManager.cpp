#include "ResourceManager.h"
#include "GameManager.h"

void ResourceManager::Initialize()
{
    Resources[ResourceID::None] = nullptr;
    LoadResourceFromFile(ResourceID::Player, L"./Images/playerShip1_blue.png");
    LoadResourceFromFile(ResourceID::Background, L"./Images/purple.png");
    LoadResourceFromFile(ResourceID::Number0, L"./Images/numeral0.png");
    LoadResourceFromFile(ResourceID::Number1, L"./Images/numeral1.png");
    LoadResourceFromFile(ResourceID::Number2, L"./Images/numeral2.png");
    LoadResourceFromFile(ResourceID::Number3, L"./Images/numeral3.png");
    LoadResourceFromFile(ResourceID::Number4, L"./Images/numeral4.png");
    LoadResourceFromFile(ResourceID::Number5, L"./Images/numeral5.png");
    LoadResourceFromFile(ResourceID::Number6, L"./Images/numeral6.png");
    LoadResourceFromFile(ResourceID::Number7, L"./Images/numeral7.png");
    LoadResourceFromFile(ResourceID::Number8, L"./Images/numeral8.png");
    LoadResourceFromFile(ResourceID::Number9, L"./Images/numeral9.png");
}

void ResourceManager::Destroy()
{
    for (auto& pair : Resources)
    {
        delete pair.second;
    }
    Resources.clear();
}

Gdiplus::Bitmap* ResourceManager::GetImage(ResourceID InID)
{
    auto iter = Resources.find(InID);   //�����ϰ�
    if (iter != Resources.end())
    {
        return iter->second;
    }
    return nullptr;
}

bool ResourceManager::LoadResourceFromFile(ResourceID InID, const wchar_t* path)
{
    bool Result = false;
    if (path)
    {
        Gdiplus::Bitmap* Image = new Gdiplus::Bitmap(path); // �̹��� �ε�
        if (Image->GetLastStatus() != Gdiplus::Ok)
        {
            // ���������� ���� �ε��� �ȉ��.
            delete Image;       // ���������� ��� ����
            Image = nullptr;
            OutputDebugString(L"�̹��� �ε� ����");
            MessageBox(GameManager::Get().GetMainWindowHandle(),
                L"�̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
        }
        else
        {
            Resources[InID] = Image;
            Result = true;
        }
    }

    return Result;
}
