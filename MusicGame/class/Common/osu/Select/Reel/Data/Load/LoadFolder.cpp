#include "LoadFolder.h"
#include"../../../../../../../_debug/_DebugConOut.h"

LoadFolder::LoadFolder()
{
	SetUp();
}

void LoadFolder::operator()(Beat::ReelData* reelData)
{
	reelData_ = reelData;
	setDataFunc_ = std::bind_front(&LoadFolder::SetData,this);
	LoadData();
}

void LoadFolder::operator()(int& count)
{
	oneLoadData_->hitObjVec.reset();
	count = 0;
	setDataFunc_ = std::bind_front(&LoadFolder::SetDataCount, this,&count);
	LoadData();
}

LoadFolder::~LoadFolder()
{
	TRACE("フォルダロード破棄\n");
}


void LoadFolder::SetUp()
{
	oneLoadData_ = std::make_shared<Beat::LoadData>();
	oneLoadData_->AllInstance();

	load_ = std::make_unique<LoadOsuFile>(oneLoadData_);
}

void LoadFolder::LoadData()
{
	//ディレクトリ探索
	for (auto& resultData : std::filesystem::directory_iterator(musicFolder))
	{
		//フォルダ
		if (resultData.is_directory())
		{
			TRACE((resultData.path().string()).c_str());
			TRACE(" これはフォルダです\n");
			LoadBeatMapFolder(resultData.path());

		}
	}
}

void LoadFolder::LoadBeatMapFolder(const std::filesystem::path& path)
{
	for (auto& resultData : std::filesystem::directory_iterator(path))
	{
		LoadFile(resultData.path());
	}
}

void LoadFolder::LoadFile(const std::filesystem::path& path)
{
	if (!load_->LoadFile(path.string()))
	{
		return;
	}
	TRACE((path.string() + "\n").c_str());
	setDataFunc_(path);
}

void LoadFolder::SetData(std::filesystem::path path)
{
	auto mapData = CreateBeatMap(path);
	reelData_->beatMapData.emplace_back(std::move(mapData));
}

void LoadFolder::SetDataCount(int* count, std::filesystem::path path)
{
	(*count)++;
}

Beat::BeatMap LoadFolder::CreateBeatMap(std::filesystem::path path)
{
	Beat::BeatMap map;
	map.filePath = std::move(path.string());
	path.remove_filename();
	map.path = path.string();
	map.image = std::move(*oneLoadData_->eventsData->image_);
	map.general = std::move(*oneLoadData_->generalData);
	map.metaDatas = std::move(*oneLoadData_->metaData);
	map.Level = oneLoadData_->scoreMagData->level;
	return map;
}


