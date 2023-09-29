#pragma once
#include"../../../HitObj.h"
#include <map>
#include<filesystem>
#include"HitSoundData.h"
#include"../../../GeneralData.h"

class DecisionCreateSound
{
public:
	DecisionCreateSound();
	Decision::HitSoundCustomSet operator()(const std::string& filePath);
private:
	using SoundTypeName = std::string;

	std::map<Beat::SampleSet, SoundTypeName> loadSoundKey_;

	std::map<const char*, Beat::Sound::TypeMode > fileName_;

	std::map<const char* ,Beat::Touch::TypeMode> touchName_;

	Decision::HitSoundCustomSet hitSoundCoustomData_;

	void SetSound(Decision::HitSoundSetData& map,const std::filesystem::path& path, const std::string& fileName);

	void SetData(std::string& copeFileName, std::pair<const char* const, Beat::Sound::TypeMode>& name, Decision::HitSoundSetData& map, 
		const Beat::SampleSet& sampleEnum, const std::filesystem::path& path);

	bool CheckTouchName(std::string& fileName);

};

