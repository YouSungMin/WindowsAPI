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
    auto iter = Resources.find(InID);   //안전하게
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
        Gdiplus::Bitmap* Image = new Gdiplus::Bitmap(path); // 이미지 로딩
        if (Image->GetLastStatus() != Gdiplus::Ok)
        {
            // 정상적으로 파일 로딩이 안됬다.
            delete Image;       // 실패했으면 즉시 해제
            Image = nullptr;
            OutputDebugString(L"이미지 로드 실패");
            MessageBox(GameManager::Get().GetMainWindowHandle(),
                L"이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
        }
        else
        {
            Resources[InID] = Image;
            Result = true;
        }
    }

    return Result;
}
