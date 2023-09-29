#include "TitleHedUpdate.h"
#include<random>
#include"../../Select/Reel/Sound/ReelSound.h"
#include"../../../../SoundWaveEffect/EqualizerEffect.h"
#include <DxLib.h>

TitleHedUpdate::TitleHedUpdate(Beat::ReelDataPtr reelData, EqualizerEffect* effect, ReelSound*& reelSound)
{
	//受け取った要素を保持
	reelData_ = std::move(reelData);
	effect_ = effect;
	reelSound_ = reelSound;
	//サウンドがない
	if (!reelSound_)
	{
		reelSound_ = new ReelSound(reelData_);
		reelSound = reelSound_;
		reelSound_->SetRandomSound();
	}
	nowSound_.second = nullptr;
	//現在の楽曲を読み込み
	auto soundData = reelSound_->LoadNowSound();
	//エフェクトデータを作成
	effect_->ChengeSound(soundData);
	//現在の曲を覚えておく
	nowSound_ = soundData;
	//再生スタート
	reelSound_->Update(false);
}

void TitleHedUpdate::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	//サウンドが止まっていたら次のサウンドに
	if (nowSound_.second != nullptr && !CheckSoundMem(*nowSound_.second) && GetSoundCurrentPosition(*nowSound_.second) != 0)
	{
		reelData_->mainSortIndex_.value()++;
		if (reelData_->mainSortIndex_.value() >= reelData_->sortData.size())
		{
			reelData_->mainSortIndex_.value() = 0;
		}
	}
	//次のサウンドに行っていたら値が返ってくる
	auto nowSound = reelSound_->Update(false);
	if (nowSound)
	{
		//エフェクトを更新する
		nowSound_ = nowSound.value();
		std::thread thread([&](){
			effect_->ChengeSound(nowSound_);
			});
		thread.detach();
	}
}
