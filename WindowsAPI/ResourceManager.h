#pragma once
#include <unordered_map>
#include "Common.h"
class ResourceManager
{
public:
	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}

	void Initialize();
	void Destroy();

	Gdiplus::Bitmap* GetImage(ResourceID InID);
private:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;	// 복사 생성자 삭제
	ResourceManager& operator=(const ResourceManager&) = delete; // 대입 연산자 삭제
	ResourceManager(const ResourceManager&&) = delete;	// 이동 생성자 삭제
	ResourceManager& operator=(const ResourceManager&&) = delete; // 이동 대입 연산자 삭제

	bool LoadResourceFromFile(ResourceID InID, const wchar_t* path);	// 파일에서 리소스를 로딩하는 함수

	std::unordered_map<ResourceID, Gdiplus::Bitmap*> Resources;	// 모든 리소스가 다 들어있는 맵
};

