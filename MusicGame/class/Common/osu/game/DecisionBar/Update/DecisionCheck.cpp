#include "DecisionCheck.h"
#include "../../../../../Input/Game/GameSceneInputKey.h"
#include "../../../../../Input/EnumCast.h"
#include"../../../Skin/Sound/SkinSound.h"
#include "../../../../../../_debug/_DebugConOut.h"
#include "../../../../../SoundVolume/SoundVolume.h"

DecisionCheck::DecisionCheck(Beat::CheckHitTime& hitTime,const Decision::HitSoundCustomSet& soundData, 
	TimingPoints::iterator& nowTimingPoint, Beat::SampleSet defSampleSet, ScoreMagDataPtr score)
	: checkHitTime_(hitTime), soundData_(soundData), nowTimingPoint_(nowTimingPoint)
{
	defSampleSet_ = defSampleSet;
	score_ = score;
}

DecisionCheck::~DecisionCheck()
{

}

bool DecisionCheck::CheckHitKey(const InputManager::InputResult* inputResult, int laneNo)
{
	return inputResult->at(laneNo).oneShot();
}


void DecisionCheck::SoundPlay(const Beat::Sound::Type& type)
{
	using namespace Decision;
	using enum Sound::Type;
	using namespace Beat;

	auto customSet = CustomSet::Def;
	int index = 0;
	if (nowTimingPoint_->sampleIndex != 0)
	{
		customSet = CustomSet::BeatMap;
		index = nowTimingPoint_->sampleIndex - 1;
	}
	auto& soundSet = soundData_.at(customSet);
	auto& hitSoundData = soundSet.at(nowTimingPoint_->sampleSet == SampleSet::NON ? defSampleSet_:nowTimingPoint_->sampleSet);
	auto soundData = hitSoundData.at(static_cast<Beat::Sound::Type>(Beat::Sound::TypeMode::Normal));

	auto normalSoundIndex = index > soundData.size() - 1 ? 0 : index;
	//PlaySoundMem(soundData[normalSoundIndex], DX_PLAYTYPE_BACK);
	lpVolumeMng.PlaySoundMem(soundData[normalSoundIndex], SE, DX_PLAYTYPE_BACK);
	if (type == static_cast<Beat::Sound::Type>(Beat::Sound::TypeMode::Normal))
	{
		return;
	}
	auto addType = static_cast<Beat::Sound::Type>(Beat::Sound::TypeMode::Whistle);
	auto max = static_cast<Beat::Sound::Type>(Beat::Sound::TypeMode::Clap) << 1;
	for (; addType < max; addType = addType << 1)
	{
		if (type & static_cast<Beat::Sound::Type>(addType))
		{
			soundData = hitSoundData.at(static_cast<Beat::Sound::Type>(addType));
			index = index > soundData.size() - 1 ? 0: index;
			//PlaySoundMem(soundData[index], DX_PLAYTYPE_BACK);
			lpVolumeMng.PlaySoundMem(soundData[index], SE, DX_PLAYTYPE_BACK);
		}
	}
}

void DecisionCheck::ConboCount(Beat::HitsDataPtr& hitsData, Beat::HitResult::Type type)
{
	if (type == Beat::HitResult::Type::BAD)
	{
		hitsData->combo = 0;
		hitsData->result[type]++;
	}
	else
	{
		hitsData->combo++;
		hitsData->result[type]++;
		hitsData->score += score_->scoreMagData[type];
	}
}

