#include "LoadConfigData.h"
#include"../../JsonParam/IOJSON.h"

/// <summary>
/// JSONで使用するデータ
/// </summary>
inline namespace JSON
{
	//ファイル名前
	constexpr const char* FileName = "config";
	constexpr const char* DefFileName = "defConfig";
	//キー
	constexpr const char* ManiaSpeed = "ManiaSpeed";
	constexpr const char* SideSpaceDivison = "SideSpaceDivison";
}


LoadConfigData::~LoadConfigData()
{
	Save();
}

LoadConfigData::LoadConfigData()
{
	configData_ = std::make_unique<Beat::ConfigData>();
}

void LoadConfigData::Save()
{
	//JSONにするデータ作成
	rapidjson::Document doc;
	doc.SetObject();
	doc.AddMember(rapidjson::StringRef(ManiaSpeed),configData_->ManiaSpeed, doc.GetAllocator());
	doc.AddMember(rapidjson::StringRef(SideSpaceDivison), configData_->SideSpaceDivison, doc.GetAllocator());
	//吐き出し
	OutPutJSON()(doc, FileName);
}

void LoadConfigData::Load()
{
	auto load = [&](auto& name){
		//JSONデータ読み込み
		auto result = InPutJSON()(name);
		//格納
		if (result)
		{
			auto& doc = result.value();
			configData_->ManiaSpeed = doc[ManiaSpeed].Get<Beat::ConfigData::mSpeed>();
			configData_->SideSpaceDivison = doc[SideSpaceDivison].Get<Beat::ConfigData::sidDivison>();
		}
	};
	//デフォルトデータ読み込み
	load(DefFileName);
	//ユーザーデータ読み込み
	load(FileName);

}

const Beat::ConfigData& LoadConfigData::GetConfigData() const
{
	return *configData_;
}

Beat::ConfigData& LoadConfigData::GetConfigChangeData()
{
	return *configData_;
}






