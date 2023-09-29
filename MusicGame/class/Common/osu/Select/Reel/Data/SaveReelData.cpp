#include "SaveReelData.h"
#include"MusicListPath.h"
#include<filesystem>


SaveReelData::SaveReelData()
{
	reelData_ = nullptr;
}

SaveReelData::~SaveReelData()
{
}

void SaveReelData::operator()(Beat::ReelData* reelData)
{
	reelData_ = reelData;
	SaveData();
}

void SaveReelData::SaveData()
{
	auto stream = std::ofstream(MusicListPath::Path, std::ios::binary);
	size_t size = 0;

	//書込みラムダ
	auto stringWrite = [&stream,&size](const std::string& string) {
		// string型のサイズを書き込む
		size = string.size();
		stream.write(reinterpret_cast<char*>(&size), sizeof(size));
		// string型を書き込む
		stream.write(string.c_str(), size);
	};
	auto write = [&stream, &size](auto& data) {
		stream.write(reinterpret_cast<char*>(&data), sizeof(data));
	};

	//マップ数
	size = reelData_->beatMapData.size();
	stream.write(reinterpret_cast<char*>(&size), sizeof(size));

	for (auto& beatMap : reelData_->beatMapData)
	{
		stringWrite(beatMap.path);
		stringWrite(beatMap.filePath);
		stringWrite(beatMap.image.filePass);
		write(beatMap.image.xOffset);
		write(beatMap.image.yOffset);
		stringWrite(beatMap.general.AudioFilename);
		write(beatMap.general.AudioLeadIn);
		write(beatMap.general.PreviewTime);
		write(beatMap.general.Mode);
		stringWrite(beatMap.metaDatas.Title);
		stringWrite(beatMap.metaDatas.Artist);
		stringWrite(beatMap.metaDatas.Version);
		stringWrite(beatMap.metaDatas.Creator);
		write(beatMap.Level);
	}


}

