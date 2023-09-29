#include "ReelSoundLoad.h"
#include<DxLib.h>
#include"ReelSound.h"
#include "../../../../../../_debug/_DebugConOut.h"


ReelSoundLoad::ReelSoundLoad()
{
	thread_ = std::jthread(std::bind_front(&ReelSoundLoad::Thread,this));
}

ReelSoundLoad::~ReelSoundLoad()
{

}

void ReelSoundLoad::LoadSound(ReelSound& reelSound)
{
	if (!reelSound.reelData_->sortData.size())
	{
		return;
	}

	auto& reelData_ = reelSound.reelData_;
	auto& soundData_ = reelSound.soundData_;
	auto& nowSound_ = reelSound.nowSound_;

	const auto& beatMap = reelData_->GetMapData();
	auto& general = beatMap->general;

	auto [itr, result] = soundData_.try_emplace(beatMap->path + general.AudioFilename);
	if (result)
	{
		itr->second = -1;
		loadingList_.emplace(std::bind(&ReelSoundLoad::LoadFunc, this, itr));
	}

	nowSound_ = std::move(itr);
}

void ReelSoundLoad::LoadNowSound(ReelSound& reelSound)
{
	if(!reelSound.reelData_->sortData.size())
	{
		return;
	}

	auto& reelData_ = reelSound.reelData_;
	auto& soundData_ = reelSound.soundData_;
	auto& nowSound_ = reelSound.nowSound_;

	const auto& beatMap = reelData_->GetMapData();
	auto& general = beatMap->general;

	auto [itr, result] = soundData_.try_emplace(beatMap->path + general.AudioFilename);
	if (result)
	{
		itr->second = -1;
		LoadFunc(itr);
	}

	nowSound_ = std::move(itr);
}

void ReelSoundLoad::Stop()
{
	thread_.request_stop();
	thread_.join();
}

void ReelSoundLoad::LoadFunc(ReelSound::SoundsData::iterator itr)
{
	itr->second = -1;
	itr->second = LoadSoundMem(itr->first.c_str());
}

void ReelSoundLoad::Thread(std::stop_token token)
{
	while (!token.stop_requested())
	{
		while (!loadingList_.empty())
		{
			if (token.stop_requested())
			{
				break;
			}
			loadingList_.front()();
			loadingList_.pop();
		}
	}

}





