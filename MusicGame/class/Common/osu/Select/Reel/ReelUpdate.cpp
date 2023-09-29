#include "ReelUpdate.h"
#include"../../../../Timer/Timer.h"
#include "../../../../Input/EnumCast.h"
#include "../../../../Input/Select/SelectSceneInput.h"
#include "Data/LoadReelData.h"
#include<DxLib.h>
#include "../../../../SoundVolume/SoundVolume.h"

constexpr int pushTime = 1 * 1000;

using namespace Sound;

ReelUpdate::ReelUpdate(Beat::ReelDataPtr reelData, ReelSound* reelSound, ReelAnimData& animData, const ChengeSceneFunc::CreateGameFunc& func)
	:sortFunc_(reelData), animData_(animData)
{
	time_ = 0;
	sound_ = reelSound?reelSound:new ReelSound(reelData);
	animData_.state = ReelAnimData::State::SeletNow;
	reelData_ = std::move(reelData);
	if (reelData_->sortData.size() == 0)
	{
		Init();
	}
	chengeGameColl_ = func;
	soundEffect_ = {
	{Sound::BeatMap,LoadSoundMem("resource/skin/Select/moveBeatMap.mp3")},
	{Sound::Group,LoadSoundMem("resource/skin/Select/moveGroup.mp3")},
	{Sound::Decision,LoadSoundMem("resource/skin/transition/start.mp3")}
	};
}

ReelUpdate::~ReelUpdate()
{
	for (auto& se : soundEffect_)
	{
		DeleteSoundMem(se.second);
	}
}
void ReelUpdate::Update(Timer::DeletaTimeConst& delta,const InputManager& input)
{
	if (!reelData_->sortData.size())
	{
		return;
	}
	if (animData_.state != ReelAnimData::State::SeletNow)
	{
		time_ += delta;
		if (time_ >= 1000)
		{
			chengeGameColl_(reelData_->GetMapData()->filePath);
		}
		return;
	}
	
	const InputManager::InputData* key = nullptr;
	auto& inputData = input.GetInputData();
	auto CheckKey = [&](SELECT&& type){
		key = &inputData.at(Cast(type));
		auto flag = key->oneShot() || ( key->pushTime >= pushTime ? key->pushTime % pushTime % 3 == 0 :false);
		return flag;
	};

	if (CheckKey(SELECT::RELOAD))
	{
		Init();
	}

	if (CheckKey(SELECT::UP))
	{
		MoveBeatMap(MoveDir::UP);
	}
	if (CheckKey(SELECT::DOWN))
	{
		MoveBeatMap(MoveDir::DOWN);
	}

	if (CheckKey(SELECT::LSKIP))
	{
		MoveMainGroup(MoveDir::UP);
	}
	if (CheckKey(SELECT::RSKIP))
	{
		MoveMainGroup(MoveDir::DOWN);
	}

	if (CheckKey(SELECT::DECIDE))
	{
		animData_.state = ReelAnimData::State::SeletEndAnim;
		//PlaySoundMem(soundEffect_[Sound::Decision], DX_PLAYTYPE_BACK, true);
		lpVolumeMng.PlaySoundMem(soundEffect_[Sound::Decision], Type::SE, DX_PLAYTYPE_BACK, false);
	}
	sound_->Update(true);

}

void ReelUpdate::Init()
{
	reelData_->reset();
	LoadReelData()(reelData_.get());
	sortFunc_.CreateSortData();
	if (reelData_->sortType)
	{
		sortFunc_.Sort(reelData_->sortType.value());

		sound_->LoadSound();
	}
	else
	{
		sortFunc_.Sort(Beat::ReelSortType::Name);
		sound_->LoadSound();
	}


	time_ = 0;



}

void ReelUpdate::MoveBeatMap(MoveDir dir)
{
	int cnt = 0;
	if (MoveDir::UP == dir)
	{
		cnt--;
	}
	if (MoveDir::DOWN == dir)
	{
		cnt++;
	}
	if (cnt != 0)
	{
		//PlaySoundMem(soundEffect_[Sound::BeatMap], DX_PLAYTYPE_BACK, true);
		lpVolumeMng.PlaySoundMem(soundEffect_[Sound::BeatMap],Type::SE, DX_PLAYTYPE_BACK, true);
	}
	if (reelData_->MoveBeatMap(cnt))
	{
		cnt = cnt > 0 ? 1 : -1;
		MoveMainGroup(cnt);
	}

}

void ReelUpdate::MoveMainGroup(MoveDir dir)
{
	int cnt = 0;
	if (MoveDir::UP == dir)
	{
		cnt--;
	}
	if (MoveDir::DOWN == dir)
	{
		cnt++;
	}
	if (cnt != 0)
	{
		//PlaySoundMem(soundEffect_[Sound::Group], DX_PLAYTYPE_BACK, true);
		lpVolumeMng.PlaySoundMem(soundEffect_[Sound::Group], Type::SE, DX_PLAYTYPE_BACK, true);
	}
	MoveMainGroup(cnt);



}

void ReelUpdate::MoveMainGroup(int cnt)
{
	if (reelData_->MoveMainSort(cnt))
	{
		cnt = cnt > 0 ? 0 : static_cast<int>(reelData_->sortData.size()) - 1;
		reelData_->mainSortIndex_ = cnt;
		reelData_->mapGroupIndex_ = (cnt == 0 ? 0 : reelData_->GetMapGroupData()->size() - 1);
	}

}

