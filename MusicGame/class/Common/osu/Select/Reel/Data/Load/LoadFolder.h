#pragma once
#include "../../ReelData.h"
#include "../../../../LoadOsu/LoadOsuFile.h"

class LoadFolder
{
public:
	LoadFolder();
	void operator()(Beat::ReelData* reelData);
	void operator()(int& count);
	~LoadFolder();
private:
	const char* musicFolder = "resource/music";

	void SetUp();
	void LoadData();
	void LoadBeatMapFolder(const std::filesystem::path& path);
	void LoadFile(const std::filesystem::path& path);
	void SetData(std::filesystem::path path);
	void SetDataCount(int* count,std::filesystem::path path);
	Beat::BeatMap CreateBeatMap(std::filesystem::path path);

	Beat::ReelData* reelData_;
	std::unique_ptr<LoadOsuFile> load_;
	Beat::LoadDataPtr oneLoadData_;
	std::function<void(std::filesystem::path)> setDataFunc_;
};

