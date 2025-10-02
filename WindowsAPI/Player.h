#pragma once
#include "Actor.h"
#include "enums.h"
#include <unordered_map>

// extern : HWND g_hMainWindow 가 다른 파일에 선언되어있다.

class Player : public Actor
{
public:
	Player() = delete;
	Player(ResourceID InID);
	~Player()override{};

	void OnRender(Gdiplus::Graphics* InGraphics)override;
	virtual void OnTick(float InDeltaTime)override;

	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	inline float GetSpeed() const { return Speed; }
	inline void SetSpeed(float InSpeed) { Speed = InSpeed; }

private:
	// 플레이어 키 입력 상태
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	////플레이어의 이동 속도
	float Speed = 150.0f;
};

