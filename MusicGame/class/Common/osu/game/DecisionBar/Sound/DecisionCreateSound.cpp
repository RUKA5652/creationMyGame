#include "DecisionCreateSound.h"
#include <filesystem>
#include"../../../Skin/FolderSearch.h"
#include<regex>
#include<DxLib.h>
#include<algorithm>
#include "../../../Skin/DefaultPath.h"

DecisionCreateSound::DecisionCreateSound()
{
	using namespace Beat;
	loadSoundKey_ =
	{
		{Beat::SampleSet::Soft,"soft"},
		{Beat::SampleSet::Normal,"normal"},
		{Beat::SampleSet::Drum,"drum"},
	};
	fileName_ =
	{
		{"normal",Sound::TypeMode::Normal},
		{"whistle",Sound::TypeMode::Whistle},
		{"clap",Sound::TypeMode::Clap},
		{"finish",Sound::TypeMode::Finish},
	};
	touchName_ =
	{
		{"hit",Touch::TypeMode::HitCircle},
		{"slider",Touch::TypeMode::Slider}
	};
}

Decision::HitSoundCustomSet DecisionCreateSound::operator()(const std::string& filePath)
{
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
	using namespace Beat::Sound;
	auto pass = std::string(Skin::Directory) + Skin::DefFilePath;

	Decision::HitSoundSetData map;
	FolderSearch search(std::bind_front(&DecisionCreateSound::SetSound, this, std::ref(map)));
	Decision::HitSoundCustomSet result;

	search(pass);
	result.emplace(Decision::CustomSet::Def,map);
	search(filePath);
	result.emplace(Decision::CustomSet::BeatMap,map);

	return result;
}

void DecisionCreateSound::SetSound(Decision::HitSoundSetData& map,const std::filesystem::path& path, const std::string& fileName)
{
	auto copeFileName = fileName;
	for (auto& [sampleEnum,sampleValue] : loadSoundKey_)
	{
		if (copeFileName.starts_with(sampleValue))
		{
			if (!CheckTouchName(copeFileName))
			{
				//ÉfÅ[É^Ç™à·Ç§
				return;
			}
			for (auto& name : fileName_)
			{
				if (copeFileName.find(name.first) != std::string::npos)
				{
					SetData(copeFileName, name, map, sampleEnum, path);
					return;
				}
			}
			//ÇªÇÍà»è„âÒÇ≥Ç»Ç¢
			return;
		}
	}
}

void  DecisionCreateSound::SetData(std::string& copeFileName, std::pair<const char* const, Beat::Sound::TypeMode>& name,
	Decision::HitSoundSetData& map, const Beat::SampleSet& sampleEnum,const std::filesystem::path& path)
{
	auto& hitSoundData = map.try_emplace(sampleEnum).first->second;
	auto& soundData = hitSoundData.try_emplace(static_cast<Beat::Sound::Type>(name.second)).first->second;
	std::smatch result;
	if (std::regex_search(copeFileName, result, std::regex(R"(\d)")))
	{
		copeFileName.erase(copeFileName.begin(), result[0].first);
		auto size = std::stoi(copeFileName);
		if (soundData.size() < size)
		{
			auto hedData = soundData.size() == 0 ? -1 : soundData[0];
			soundData.resize(std::stoi(copeFileName), -1);
			std::ranges::replace_if(soundData, [](auto i) { return i == -1; }, hedData);
		}
		soundData[size - 1] = LoadSoundMem(path.string().c_str(),8);
	}
	else
	{
		if (soundData.size() == 0)
		{
			soundData.emplace_back(LoadSoundMem(path.string().c_str(),8));
		}
		else
		{
			auto newHandle = LoadSoundMem(path.string().c_str(),8);
			auto oldHandle = soundData[0];
			std::ranges::replace_if(soundData, [&](auto i) { return i == oldHandle; }, newHandle);
		}

	}
}

bool DecisionCreateSound::CheckTouchName(std::string& fileName)
{
	for (auto& name : touchName_)
	{
		auto pos = fileName.find(name.first);
		if (pos != std::string::npos)
		{
			fileName = fileName.substr(pos);
			return true;
		}
	}
	return false;
}
