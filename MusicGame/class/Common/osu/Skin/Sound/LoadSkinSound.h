#pragma once
#include<string>
#include<filesystem>
#include <map>
#include"SkinSoundData.h"
#include "../DefaultPath.h"

class LoadSkinSound
{
public:

	LoadSkinSound();

	Beat::SkinSoundMap LoadData(const std::string& fileName);
	void LoadData(const std::string& fileName, Beat::SkinSoundMap& map);

private:
	const std::string directory = Skin::Directory;

	std::map<std::string, Beat::SkinSoundType> soundName_;

	void CreateSoundName();

	void SetSound(Beat::SkinSoundMap& map, const std::filesystem::path& path, const std::string& fileName);
};

