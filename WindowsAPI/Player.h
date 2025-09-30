#pragma once
#include <unordered_map>
#include <Windows.h>
#include <gdiplus.h>
#include "enums.h"


// extern : HWND g_hMainWindow �� �ٸ� ���Ͽ� ����Ǿ��ִ�.
extern HWND g_hMainWindow;
extern Gdiplus::Point g_ScreenSize;
using PointF = Gdiplus::PointF;

class Player
{
public:
	Player() = delete;
	Player(const wchar_t* InImagePath);
	~Player();

	void Render(Gdiplus::Graphics* InGraphics);
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

private:
	// �÷��̾� Ű �Է� ����
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	// �÷��̾��� �߽���
	PointF Pivot = {0.5f , 0.5f};	//Pivot �⺻ ���� �Ѱ��

	//�÷��̾��� ��ġ
	PointF Position{ 0.0f, 0.0f };

	//�÷��̾��� �̵� �ӵ�
	float Speed = 10.0f;

	// �÷��̾ �׷��� ũ��
	static constexpr int PixelSize = 64;

	// �÷��̾� �̹����� ������� ��Ʈ��
	Gdiplus::Bitmap* Image = nullptr;   // �÷��̾ �׷��� ����
};

