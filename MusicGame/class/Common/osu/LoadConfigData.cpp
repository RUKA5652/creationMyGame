#include "LoadConfigData.h"
#include"../../JsonParam/IOJSON.h"

/// <summary>
/// JSON�Ŏg�p����f�[�^
/// </summary>
inline namespace JSON
{
	//�t�@�C�����O
	constexpr const char* FileName = "config";
	constexpr const char* DefFileName = "defConfig";
	//�L�[
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
	//JSON�ɂ���f�[�^�쐬
	rapidjson::Document doc;
	doc.SetObject();
	doc.AddMember(rapidjson::StringRef(ManiaSpeed),configData_->ManiaSpeed, doc.GetAllocator());
	doc.AddMember(rapidjson::StringRef(SideSpaceDivison), configData_->SideSpaceDivison, doc.GetAllocator());
	//�f���o��
	OutPutJSON()(doc, FileName);
}

void LoadConfigData::Load()
{
	auto load = [&](auto& name){
		//JSON�f�[�^�ǂݍ���
		auto result = InPutJSON()(name);
		//�i�[
		if (result)
		{
			auto& doc = result.value();
			configData_->ManiaSpeed = doc[ManiaSpeed].Get<Beat::ConfigData::mSpeed>();
			configData_->SideSpaceDivison = doc[SideSpaceDivison].Get<Beat::ConfigData::sidDivison>();
		}
	};
	//�f�t�H���g�f�[�^�ǂݍ���
	load(DefFileName);
	//���[�U�[�f�[�^�ǂݍ���
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






