#pragma once
#include<string>
#include <optional>
#include<memory>
#include<functional>
#include"LoadFunc.h"
#include"../../LoadData.h"

namespace Beat
{
	class LoadModule
	{
	public:
		virtual ~LoadModule() {};
		virtual bool LoadFile(const std::string& fileData, Beat::LoadDataPtr data) { return true; };
	};
}

/// <summary>
/// セクションロード基底クラス
/// </summary>
/// <typeparam name="T">ファイル情報</typeparam>
template<class T>
class LoadSectionBase :
	public Beat::LoadModule
{
public:
	using DataPtr = T*;

	LoadSectionBase(std::string title);
	~LoadSectionBase();

	/// <summary>
	/// ファイル読み込み
	/// </summary>
	/// <param name="fileData">ファイルパス</param>
	/// <returns>成否フラグ</returns>
	bool LoadFile(const std::string& fileData, DataPtr data);
protected:

	using setDataFunc = std::function<bool(T&, const std::string&)>;

	//読み込みデータTitle
	const std::string title_;

	//読み込みデータ作成関数配列 
	std::vector<setDataFunc> setDataFuncVec_;

	//ロード関数
	std::unique_ptr<LoadFunc::LoadFile<T>> loadFileFunc_;

	void Init();
	//ファイル情報を抜き出す
	std::optional<std::string> GetHitObjString(const std::string& fileData);

	virtual void SetData(const std::string& fileData, DataPtr dataPtr) ;


};

#include"LoadSectionBase/LoadSectionBase.h"


