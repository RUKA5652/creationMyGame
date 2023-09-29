#include "HistoryScoreLoad.h"
#include<filesystem>
#include<fstream>


HistoryScore HistoryScoreLoad::Load(std::string musicFolderPath)
{
	HistoryScore result;
	std::string checkName("resource/music");
	auto hitPos = musicFolderPath.find_first_of(checkName);
	if (hitPos == std::string::npos)
	{
		return result;
	}
	musicFolderPath.replace(hitPos, checkName.size() - 1, FolderName);
	hitPos = musicFolderPath.find_last_of('.');
	if (hitPos == std::string::npos)
	{
		return result;
	}
	musicFolderPath.replace(hitPos + 1, musicFolderPath.size() - 1, Extension);

	//ì«Ç›çûÇ›
	if (std::filesystem::exists(musicFolderPath))
	{
		std::ifstream stream(musicFolderPath, std::ios::binary);
		int data = 0;
		int cnt = 0;
		stream.read(reinterpret_cast<char*>(&cnt), sizeof(cnt));
		for(int i = 0; i < cnt;i++)
		{
			stream.read(reinterpret_cast<char*>(&data), sizeof(data));
			result.push_back(data);
		}
	}

	return result;

}
