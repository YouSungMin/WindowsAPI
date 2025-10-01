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

    MainPlayer = new Player(L"./Images/playerShip1_blue.png");
    MainPlayer->SetRenderLayer(RenderLayer::Player);
    AddActor(MainPlayer);
    TestActor* testActor = new TestActor();
    testActor->SetRenderLayer(RenderLayer::Test);
    AddActor(testActor);
    BackGround* background = new BackGround(L"./Images/purple.png");
    background->SetRenderLayer(RenderLayer::Background);
    AddActor(background);
}

void GameManager::Destroy()
{
    for (const auto& pair : RenderLayers)
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
    RenderLayers.clear();

    delete BackBufferGraphics;
    BackBufferGraphics = nullptr;
    delete BackBuffer;
    BackBuffer = nullptr;
}

void GameManager::Tick(float InDeltaTime)
{
    for (const auto& pair : RenderLayers)
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
    //for (Actor* Actor : Actors)
    //{
    //    Actor->OnTick(InDeltaTime);

    //}
}

void GameManager::Render()
{
    if (BackBufferGraphics)   // g_BackBufferGraphics �ʼ�
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));

        //for (Actor* Actor : Actors)
        //{
        //    Actor->OnRender(BackBufferGraphics);
        for (const auto& pair : RenderLayers)
        {
            // �ش� ���̾ ���� ��� ���͵��� �������մϴ�.
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

void GameManager::AddActor(Actor* InActor)
{
    if (InActor == nullptr) return;
    RenderLayer layer = InActor->GetRenderLayer();

    RenderLayers[layer].push_back(InActor);
    //Actors.push_back(InActor);
}
