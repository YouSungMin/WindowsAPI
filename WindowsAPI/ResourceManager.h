#pragma once
class ResourceManager
{
public:
	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}
private:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;	// ���� ������ ����
	ResourceManager& operator=(const ResourceManager&) = delete; // ���� ������ ����
	ResourceManager(const ResourceManager&&) = delete;	// �̵� ������ ����
	ResourceManager& operator=(const ResourceManager&&) = delete; // �̵� ���� ������ ����

};

