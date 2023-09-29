#include "ReelSound.h"
#include<DxLib.h>
#include<thread>
#include "../../../../../SoundVolume/SoundVolume.h"
#include "../../../../../RandSeed/RandSeed.h"
#include <random>

ReelSound::ReelSound(Beat::ReelDataPtr reelData)
{
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);
	reelData_ = std::move(reelData);
}


ReelSound::~ReelSound()
{
	load_.Stop();
	lpVolumeMng.RemoveSetFollowingHandle(nowSound_->second, Sound::Type::Song);
	StopSoundMem(nowSound_->second);

	for (auto& data : soundData_)
	{
		if (data.second <= 0)
		{
			continue;
		}
		DeleteSoundMem(data.second, true);
	}
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
}

std::optional<std::pair<std::string, int*>> ReelSound::Update(bool flag)
{
	std::optional<std::pair<std::string, int*>> result = std::nullopt;
	auto data = reelData_->GetMapData();
	if (nowSound_->first != data->path + data->general.AudioFilename)
	{
		StopSoundMem(nowSound_->second);
		LoadSound();
		result = { nowSound_->first,&nowSound_->second };
	}

	if (!CheckSoundMem(nowSound_->second))
	{
		if (!flag && GetSoundCurrentPosition(nowSound_->second) != 0)
		{
			return result;
		}
		LoadSound();

		lpVolumeMng.SetFollowingHandle(nowSound_->second, Sound::Type::Song);
		lpVolumeMng.PlaySoundMem(nowSound_->second, Sound::Type::Song, DX_PLAYTYPE_BACK, flag);

	}
	return result;
}

std::pair<std::string, int*> ReelSound::LoadSound()
{
	load_.LoadSound(*this);
	return { nowSound_->first,&nowSound_->second };
	
}

std::pair<std::string, int*> ReelSound::LoadNowSound()
{
	load_.LoadNowSound(*this);
	return { nowSound_->first,&nowSound_->second };
}

void ReelSound::SetRandomSound()
{
	auto sortDataSize = reelData_->sortData.size();
	std::mt19937_64 rand = std::mt19937_64(lpSeedMng.GetSeed());
	auto num = rand();
	auto sortDataNum = static_cast<int>(num % sortDataSize);
	auto& data = reelData_->sortData[sortDataNum][0];
	reelData_->mainSortIndex_ = sortDataNum;
	reelData_->mapGroupIndex_ = 0;
}



