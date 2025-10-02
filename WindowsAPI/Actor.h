#pragma once
#include "Common.h"

class Actor
{
public:
	Actor() = delete;
	Actor(ResourceID InID);
	virtual ~Actor() = default;

	virtual void OnRender(Gdiplus::Graphics* InGraphics);
	virtual void OnTick(float InDeltaTime);

	//Getter
	inline const PointF& GetPosition() const{ return Position; }
	inline int GetSize() const { return Size; }
	inline const PointF& GetPivot() const { return Pivot; }
	inline RenderLayer GetRenderLayer() { return TargetRenderLayer; }

	//Setter
	inline void SetPosition(float InX, float InY) { Position.X = InX; Position.Y = InY; }
	inline void SetSize(int InSize) { Size = InSize; }
	inline void SetPivot(float InX, float InY) { Pivot.X = InX; Pivot.Y = InY; }
	inline void SetRenderLayer(RenderLayer InLayer) { TargetRenderLayer = InLayer; }

protected:
	// 그려질 크기
	int Size = 64;

	// 플레이어의 중심점
	PointF Pivot = { 0.5f , 0.5f };	//Pivot 기본 값은 한가운데

	//플레이어의 위치
	PointF Position{ 0.0f, 0.0f };

	// 플레이어 이미지가 들어있을 비트맵
	Gdiplus::Bitmap* Image = nullptr;   // 플레이어가 그려질 종이

	RenderLayer TargetRenderLayer = RenderLayer::Misc;
};

