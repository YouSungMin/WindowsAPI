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
        // 혹시 안만들어졌을 때를 대비한 에러 출력
        MessageBox(hMainWindow, L"백 버퍼 그래픽스 생성 실패", L"오류", MB_OK | MB_ICONERROR);
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
        // 각 레이어(pair.second)에 있는 벡터를 순회합니다.
        for (Actor* actor : pair.second)
        {
            if (actor)
            {
                delete actor; // 각 Actor 객체의 메모리 해제
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
        // 해당 레이어에 속한 모든 액터들을 렌더링합니다.
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
    if (BackBufferGraphics)   // g_BackBufferGraphics 필수
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));

        //for (Actor* Actor : Actors)
        //{
        //    Actor->OnRender(BackBufferGraphics);
        for (const auto& pair : RenderLayers)
        {
            // 해당 레이어에 속한 모든 액터들을 렌더링합니다.
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
