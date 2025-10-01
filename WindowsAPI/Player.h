#pragma once
#include <unordered_map>
#include "Common.h"
#include "enums.h"


// extern : HWND g_hMainWindow �� �ٸ� ���Ͽ� ����Ǿ��ִ�.

class Player
{
public:
	Player() = delete;
	Player(const wchar_t* InImagePath);
	~Player();

	void Render(Gdiplus::Graphics* InGraphics);
	void HandleKeyState(WPARAM InKey, bool InIsPressed);
	void Tick(float InDeltaTime);

private:
	// �÷��̾ �׷��� ũ��
	static constexpr int PixelSize = 64;

	// �÷��̾� Ű �Է� ����
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	// �÷��̾��� �߽���
	PointF Pivot = {0.5f , 0.5f};	//Pivot �⺻ ���� �Ѱ��

	//�÷��̾��� ��ġ
	PointF Position{ 0.0f, 0.0f };

	//�÷��̾��� �̵� �ӵ�
	float Speed = 150.0f;


	// �÷��̾� �̹����� ������� ��Ʈ��
	Gdiplus::Bitmap* Image = nullptr;   // �÷��̾ �׷��� ����
};

