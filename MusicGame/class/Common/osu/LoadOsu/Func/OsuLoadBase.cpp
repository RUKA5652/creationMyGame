#include "OsuLoadBase.h"
#include"OpunOsuFile.h"
#include<filesystem>

OsuLoadBase::OsuLoadBase(int&& version, 
	Beat::LoadDataPtr& loadData)
	:version(version),loadData_(loadData)
{
	Init();
}

OsuLoadBase::~OsuLoadBase()
{
	loadData_.reset();
	for (auto module : loadModule_)
	{
		delete module;
	}
}

bool OsuLoadBase::LoadOsuFile(const std::string& filePass)
{
	auto opunResult = OpunOsuFile()(filePass);
	if (!opunResult.has_value())
	{
		return false;
	}
	auto& data = opunResult.value();
	std::filesystem::path path(filePass);
	loadData_->folderPath = path.remove_filename().string();
	for (auto& module : loadModule_)
	{
		module->LoadFile(data, loadData_);
	}



	return true;
}

void OsuLoadBase::Init()
{
	if (!loadData_)
	{
		throw std::range_error("äiî[êÊÇ»Çµ");
	}
}



