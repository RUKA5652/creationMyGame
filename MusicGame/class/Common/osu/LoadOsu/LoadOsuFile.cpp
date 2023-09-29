#include "LoadOsuFile.h"
#include"OsuCheckVersion.h"
#include "Func/Load/DefaultOsuLoad.h"

//該当バージョンのファイルがないときにトライするバージョン
constexpr int tryNum = 0;

LoadOsuFile::LoadOsuFile()
{
	loadData_ = std::make_shared<Beat::LoadData>();
	loadData_->AllInstance();
	SetUp();
}

LoadOsuFile::LoadOsuFile(Beat::LoadDataPtr& Target)
{
	loadData_ = Target;
	//Target.reset();
	SetUp();
}

LoadOsuFile::LoadOsuFile(Beat::LoadDataPtr&& Target)
	:LoadOsuFile(Target)
{
}

LoadOsuFile::~LoadOsuFile()
{
	for (auto& func : funcData_)
	{
		func.second.reset();
	}
	loadData_.reset();
}

bool LoadOsuFile::LoadFile(const std::string& filePass)
{
	auto [flag,version] = CheckVersion(filePass);
	if (!flag)
	{
		return funcData_[tryNum]->LoadOsuFile(filePass);
	}
	return funcData_[version]->LoadOsuFile(filePass);
}

Beat::LoadDataCPtr LoadOsuFile::GetLoadData()
{
	return loadData_;
}


std::pair<bool, int> LoadOsuFile::CheckVersion(const std::string& filePass)
{	
	//バージョンを取得する
	auto version = Beat::CheckVersion()(filePass);
	if (!funcData_.count(version))
	{
		return { false,version };
	}
	return { true,version };
}

void LoadOsuFile::SetUp()
{
	funcData_.clear();
	auto ptr = std::make_unique<DefaultOsuLoad>(loadData_);
	funcData_.emplace(ptr->version, std::move(ptr));
}
