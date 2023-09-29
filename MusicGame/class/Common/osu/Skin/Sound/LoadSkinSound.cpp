#include "LoadSkinSound.h"
#include<typeinfo>
#include<DxLib.h>
#include<regex>
#include<iostream>
#include"../FolderSearch.h"

LoadSkinSound::LoadSkinSound()
{
	CreateSoundName();
}

Beat::SkinSoundMap LoadSkinSound::LoadData(const std::string& fileName)
{
	Beat::SkinSoundMap map;
	FolderSearch(std::bind_front(&LoadSkinSound::SetSound, this, std::ref(map)))(directory + fileName);
	return map;
}

void LoadSkinSound::LoadData(const std::string& fileName, Beat::SkinSoundMap& map)
{
	FolderSearch(std::bind_front(&LoadSkinSound::SetSound, this, std::ref(map)))(directory + fileName);
}

void LoadSkinSound::CreateSoundName()
{
	//
	soundName_ =
	{
		{"combobreak",Beat::SkinSoundType::ComboBreak}
	};
	
}

void LoadSkinSound::SetSound(Beat::SkinSoundMap& map, const std::filesystem::path& path, const std::string& fileName)
{
	if (soundName_.count(fileName))
	{
		map[soundName_[fileName]].emplace_back(LoadSoundMem(path.string().c_str()));
	}

}

