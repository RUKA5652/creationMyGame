#pragma once
#include<map>
#include <memory>
#include"Func/OsuLoadBase.h"
#include"../LoadData.h"



class LoadOsuFile
{
public:
	LoadOsuFile();
	LoadOsuFile(Beat::LoadDataPtr& Target);
	LoadOsuFile(Beat::LoadDataPtr&& Target);
	~LoadOsuFile();
	/// <summary>
	/// ファイル情報をすべて読み込む
	/// </summary>
	/// <param name="filePass">読み込みファイルのパス</param>
	/// <returns></returns>
	bool LoadFile(const std::string& filePass);


	Beat::LoadDataCPtr GetLoadData();
private:
	std::map<int, std::unique_ptr<OsuLoadBase>> funcData_;
	
	std::pair<bool,int> CheckVersion(const std::string& filePass);

	void SetUp();

	Beat::LoadDataPtr loadData_;

};

