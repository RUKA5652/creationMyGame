#include "HistoryScoreSave.h"
#include<fstream>
#include<filesystem>

bool HistoryScoreSave::Save(std::string musicFolderPath, const HistoryScore& data)
{
	std::string checkName("resource/music");
	auto hitPos = musicFolderPath.find_first_of(checkName);
	if (hitPos == std::string::npos)
	{
		return false;
	}
	musicFolderPath.replace(hitPos, checkName.size() - 1, FolderName);
	hitPos = musicFolderPath.find_last_of('.');
	if (hitPos == std::string::npos)
	{
		return false;
	}
	musicFolderPath.replace(hitPos + 1, musicFolderPath.size() - 1, Extension);
	std::filesystem::path path(musicFolderPath);
	path.remove_filename();
	std::filesystem::create_directories(path);

	auto stream = std::ofstream(musicFolderPath, std::ios::binary);
	int size = static_cast<int>(data.size());
	stream.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (int score : data)
	{
		stream.write(reinterpret_cast<char*>(&score), sizeof(score));
	}

	return true;
}
