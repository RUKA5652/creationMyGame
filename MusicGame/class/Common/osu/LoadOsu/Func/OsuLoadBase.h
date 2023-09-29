#pragma once
#include <string>
#include<fstream>
#include<memory>
#include "../../LoadData.h"
#include"LoadSectionBase.h"



/// <summary>
/// osuファイル読み込みクラス
/// </summary>
class OsuLoadBase
{
public:
	const int version;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="version">バージョン情報</param>
	/// <param name="loadData">ロードデータ格納先</param>
	OsuLoadBase(int&& version, Beat::LoadDataPtr& loadData);
	virtual ~OsuLoadBase();
	/// <summary>
	/// ファイル情報を読み込む
	/// </summary>
	/// <param name="filePass">読み込みファイルのパス</param>
	/// <returns></returns>
	virtual bool LoadOsuFile(const std::string& filePass);
protected:
	std::vector<Beat::LoadModule*> loadModule_;

	Beat::LoadDataPtr loadData_;


	void Init();


};
