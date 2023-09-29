#include"SkinSound.h"
#include"../DefaultPath.h"

const Beat::SoundData& SkinSound::GetSound(Beat::SkinSoundType&& type)
{
	return skinMap_.at(type);
}

const Beat::SkinSoundMap& SkinSound::GetAllSound()
{
	return skinMap_;
}

SkinSound::SkinSound()
{
	skinMap_ = loadSkin.LoadData(Skin::DefFilePath);
}

SkinSound::~SkinSound()
{
}

