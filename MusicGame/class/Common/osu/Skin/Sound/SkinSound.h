#pragma once
#include<string>
#include<forward_list>
#include<map>
#include"SkinSoundData.h"
#include"LoadSkinSound.h"

#define lpSkinSoundPtr SkinSound::GetInstance()

class SkinSound
{
public:
	static SkinSound& GetInstance()
	{
		static SkinSound skin_;
		return skin_;
	};
	
	const Beat::SoundData &GetSound(Beat::SkinSoundType&& type);
	const Beat::SkinSoundMap& GetAllSound();
private:
	SkinSound();
	~SkinSound();

	Beat::SkinSoundMap skinMap_;

	LoadSkinSound loadSkin;

};

