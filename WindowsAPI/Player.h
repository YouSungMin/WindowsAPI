#pragma once
#include "Actor.h"
#include "enums.h"
#include <unordered_map>

// extern : HWND g_hMainWindow �� �ٸ� ���Ͽ� ����Ǿ��ִ�.

class Player : public Actor
{
public:
	Player() = delete;
	Player(const wchar_t* InImagePath);
	~Player()override{};

	void OnRender(Gdiplus::Graphics* InGraphics)override;
	virtual void OnTick(float InDeltaTime)override;

	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	inline float GetSpeed() const { return Speed; }
	inline void SetSpeed(float InSpeed) { Speed = InSpeed; }

private:
	// �÷��̾� Ű �Է� ����
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	////�÷��̾��� �̵� �ӵ�
	float Speed = 150.0f;
};

