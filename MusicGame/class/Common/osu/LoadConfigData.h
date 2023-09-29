#pragma once
#include<memory>
#include"ConfigData.h"

#define lpConfigData LoadConfigData::GetInstance()
/// <summary>
/// コンフィグデータ読み込み・データ管理
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
	//保存
	void Save();
	//読み込み
	void Load();
};


