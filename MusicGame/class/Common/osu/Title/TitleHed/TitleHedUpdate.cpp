#include "TitleHedUpdate.h"
#include<random>
#include"../../Select/Reel/Sound/ReelSound.h"
#include"../../../../SoundWaveEffect/EqualizerEffect.h"
#include <DxLib.h>

TitleHedUpdate::TitleHedUpdate(Beat::ReelDataPtr reelData, EqualizerEffect* effect, ReelSound*& reelSound)
{
	//�󂯎�����v�f��ێ�
	reelData_ = std::move(reelData);
	effect_ = effect;
	reelSound_ = reelSound;
	//�T�E���h���Ȃ�
	if (!reelSound_)
	{
		reelSound_ = new ReelSound(reelData_);
		reelSound = reelSound_;
		reelSound_->SetRandomSound();
	}
	nowSound_.second = nullptr;
	//���݂̊y�Ȃ�ǂݍ���
	auto soundData = reelSound_->LoadNowSound();
	//�G�t�F�N�g�f�[�^���쐬
	effect_->ChengeSound(soundData);
	//���݂̋Ȃ��o���Ă���
	nowSound_ = soundData;
	//�Đ��X�^�[�g
	reelSound_->Update(false);
}

void TitleHedUpdate::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	//�T�E���h���~�܂��Ă����玟�̃T�E���h��
	if (nowSound_.second != nullptr && !CheckSoundMem(*nowSound_.second) && GetSoundCurrentPosition(*nowSound_.second) != 0)
	{
		reelData_->mainSortIndex_.value()++;
		if (reelData_->mainSortIndex_.value() >= reelData_->sortData.size())
		{
			reelData_->mainSortIndex_.value() = 0;
		}
	}
	//���̃T�E���h�ɍs���Ă�����l���Ԃ��Ă���
	auto nowSound = reelSound_->Update(false);
	if (nowSound)
	{
		//�G�t�F�N�g���X�V����
		nowSound_ = nowSound.value();
		std::thread thread([&](){
			effect_->ChengeSound(nowSound_);
			});
		thread.detach();
	}
}
