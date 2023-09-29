#include "GameClock.h"
#include<Dxlib.h>
#include "../../../_debug/_DebugConOut.h"
#include"WaitSound.h"
#include "../../SoundVolume/SoundVolume.h"

GameClock::GameClock(const std::string& audioFile, Beat::LoadDataCPtr data,int& handle)
{
	handle_ = -1;
	handle_ = LoadSoundMem(audioFile.c_str());
	handle = handle_;
	playFlag_ = false;

	auto& firstTimingPoints = (*data->timingPoints)[0];
	beatLength_ = firstTimingPoints.beatLength;
	meter_ = firstTimingPoints.meter;

	leadInTime_ = data->generalData->AudioLeadIn;
	leadInTime_ += static_cast<Beat::UpdateTime>((beatLength_ * meter_) * 2);
	deltaTime_ -= leadInTime_;

	func_ = std::bind(&GameClock::WaitUpdate,this);
	waitSound_ = new WaitSound(beatLength_,meter_);
}

GameClock::~GameClock()
{
	lpVolumeMng.RemoveSetFollowingHandle(handle_, Sound::Type::Song);
	StopSoundMem(handle_);
	DeleteSoundMem(handle_);
	delete waitSound_;
	waitSound_ = nullptr;
}

void GameClock::UpdateDelta()
{
	func_();
}

void GameClock::MusicUpdate()
{
	auto total = GetSoundTotalTime(handle_);
	auto cureent = GetSoundCurrentTime(handle_);
	if (!CheckSoundMem(handle_) && !playFlag_)
	{
		lpVolumeMng.SetFollowingHandle(handle_, Sound::Type::Song);
		lpVolumeMng.PlaySoundMem(handle_, Sound::Type::Song, DX_PLAYTYPE_BACK);
		playFlag_ = true;
	}
	if (total == cureent)
	{
		StopSoundMem(handle_);
		SetCurrentPositionSoundMem(0,handle_);
	}
	deltaTime_ = static_cast<DeletaTime>(GetSoundCurrentTime(handle_));
}

void GameClock::WaitUpdate()
{
	endTime = std::chrono::system_clock::now();
	auto delta = static_cast<DeletaTime>((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()));
	startTime = std::chrono::system_clock::now();
	deltaTime_ += delta;

	waitSound_->WaitPlaySound(delta);

	if (deltaTime_ >= 0)
	{
		delete waitSound_;
		waitSound_ = nullptr;
		func_ = std::bind(&GameClock::MusicUpdate, this);
		func_();
	}
}



