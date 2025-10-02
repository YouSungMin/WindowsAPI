#include "GameManager.h"
#include "Background.h"
#include "Player.h"
#include "TestActor.h"

void GameManager::Initialize()
{
    BackBuffer = new Gdiplus::Bitmap(
        GameManager::ScreenWidth, GameManager::ScreenHeight, PixelFormat32bppARGB);
    BackBufferGraphics = Gdiplus::Graphics::FromImage(BackBuffer);
    if (!BackBufferGraphics)
    {
        // Ȥ�� �ȸ�������� ���� ����� ���� ���
        MessageBox(hMainWindow, L"�� ���� �׷��Ƚ� ���� ����", L"����", MB_OK | MB_ICONERROR);
    }

    MainPlayer = new Player(ResourceID::Player);
    MainPlayer->SetRenderLayer(RenderLayer::Player);
    AddActor(RenderLayer::Player,MainPlayer);
    TestActor* testActor = new TestActor();
    testActor->SetRenderLayer(RenderLayer::Test);
    AddActor(RenderLayer::Test,testActor);
    BackGround* background = new BackGround(ResourceID::Background);
    background->SetRenderLayer(RenderLayer::Background);
    AddActor(RenderLayer::Background,background);
}

void GameManager::Destroy()
{
    for (const auto& pair : Actors)
    {
        // �� ���̾�(pair.second)�� �ִ� ���͸� ��ȸ�մϴ�.
        for (Actor* actor : pair.second)
        {
            if (actor)
            {
                delete actor; // �� Actor ��ü�� �޸� ����
            }
        }
    }
    Actors.clear();

    delete BackBufferGraphics;
    BackBufferGraphics = nullptr;
    delete BackBuffer;
    BackBuffer = nullptr;
}

void GameManager::Tick(float InDeltaTime)
{
    for (const auto& pair : Actors)
    {
        // �ش� ���̾ ���� ��� ���͵��� �������մϴ�.
        for (Actor* actor : pair.second)
        {
            if (actor)
            {
                actor->OnTick(InDeltaTime);
            }
        }
    }
}

void GameManager::Render()
{
    if (BackBufferGraphics)   // g_BackBufferGraphics �ʼ�
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));

        for (const auto& pair : Actors)
        {
            for (Actor* actor : pair.second)
            {
                if (actor)
                {
                    actor->OnRender(BackBufferGraphics);
                }
            }
        }
    }
}

void GameManager::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    MainPlayer->HandleKeyState(InKey, InIsPressed);
}

