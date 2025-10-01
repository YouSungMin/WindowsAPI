#pragma once
#include "Common.h"

class Actor
{
public:
	Actor() = delete;
	Actor(const wchar_t* InImagePath);
	virtual ~Actor();

	virtual void OnRender(Gdiplus::Graphics* InGraphics);
	virtual void OnTick(float InDeltaTime);

	//Getter
	inline const PointF& GetPosition() const{ return Position; }
	inline int GetSize() const { return Size; }
	inline const PointF& GetPivot() const { return Pivot; }

	//Setter
	inline void SetPosition(float InX, float InY) { Position.X = InX; Position.Y = InY; }
	inline void SetSize(int InSize) { Size = InSize; }
	inline void SetPivot(float InX, float InY) { Pivot.X = InX; Pivot.Y = InY; }

protected:
	// �׷��� ũ��
	int Size = 64;

	// �÷��̾��� �߽���
	PointF Pivot = { 0.5f , 0.5f };	//Pivot �⺻ ���� �Ѱ��

	//�÷��̾��� ��ġ
	PointF Position{ 0.0f, 0.0f };

	// �÷��̾� �̹����� ������� ��Ʈ��
	Gdiplus::Bitmap* Image = nullptr;   // �÷��̾ �׷��� ����
};

