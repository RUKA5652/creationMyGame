#include "LoadReelData.h"
#include"../ReelData.h"
#include"../../../../../../_debug/_DebugConOut.h"
#include<regex>
#include"SaveReelData.h"
#include"MusicListPath.h"

LoadReelData::LoadReelData()
{
	reelData_ = nullptr;
}

void LoadReelData::operator()(Beat::ReelData* reelData)
{
	reelData_ = reelData;
	if (!CheckMusicList() || !CheckBeatMapCount())
	{
		load_(reelData_);
		SaveReelData()(reelData_);
	}
	else
	{
		LoadListData();
	}
}

bool LoadReelData::CheckMusicList()
{
	return std::filesystem::exists(MusicListPath::Path);
}

bool LoadReelData::CheckBeatMapCount()
{
	if (!CheckMusicList())
	{
		return false;
	}
	int count;
	load_(count);
	std::ifstream stream(MusicListPath::Path, std::ios::binary);
	size_t mapNum = 0;
	stream.read(reinterpret_cast<char*>(&mapNum), sizeof(mapNum));
	return mapNum == count;
}

void LoadReelData::LoadListData()
{
	std::ifstream stream(MusicListPath::Path, std::ios::binary);
	size_t size = 0;
	size_t mapNum = 0;
	//読み込みラムダ
	auto stringRead = [&stream, &size](std::string& string) {
		// string型のサイズを書き込む
		stream.read(reinterpret_cast<char*>(&size), sizeof(size));
		string = std::string();
		string.resize(size);
		// string型を書き込む
		stream.read(string.data(), size);
	};

	auto read = [&stream, &size](auto& data) {
		auto size = sizeof(data);
		stream.read(reinterpret_cast<char*>(&data), sizeof(data));
	};

	stream.read(reinterpret_cast<char*>(&mapNum), sizeof(mapNum));

	while (stream) 
	{
		if (reelData_->beatMapData.size() == mapNum)
		{
			return;
		}
		Beat::BeatMap beatMap;
		stringRead(beatMap.path);
		stringRead(beatMap.filePath);
		stringRead(beatMap.image.filePass);
		read(beatMap.image.xOffset);
		read(beatMap.image.yOffset);
		stringRead(beatMap.general.AudioFilename);
		read(beatMap.general.AudioLeadIn);
		read(beatMap.general.PreviewTime);
		read(beatMap.general.Mode);
		stringRead(beatMap.metaDatas.Title);
		stringRead(beatMap.metaDatas.Artist);
		stringRead(beatMap.metaDatas.Version);
		stringRead(beatMap.metaDatas.Creator);
		read(beatMap.Level);
		reelData_->beatMapData.emplace_back(beatMap);
	}


}

