#pragma once
#include<memory>
#include"ConfigData.h"

#define lpConfigData LoadConfigData::GetInstance()
/// <summary>
/// �R���t�B�O�f�[�^�ǂݍ��݁E�f�[�^�Ǘ�
/// </summary>
class LoadConfigData
{
public:
	~LoadConfigData();

	static LoadConfigData* GetInstance()
	{
		static LoadConfigData ptr;
		return &ptr;
	}

	const Beat::ConfigData& GetConfigData() const;
	Beat::ConfigData& GetConfigChangeData();
private:
	LoadConfigData();
	LoadConfigData(LoadConfigData&) = delete;
	LoadConfigData(LoadConfigData*) = delete;

	std::unique_ptr<Beat::ConfigData> configData_;
	//�ۑ�
	void Save();
	//�ǂݍ���
	void Load();
};


