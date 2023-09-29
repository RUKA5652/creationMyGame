#include "ResultUpdate.h"
#include "../../../Input/Result/ResultSceneInputKey.h"
#include "../../../Input/EnumCast.h"
#include "../../../SoundVolume/SoundVolume.h"

constexpr auto blendPrm = 0.5f;
constexpr auto NonblendPrm = 1.0f;

ResultUpdate::ResultUpdate(ResultSharingDataConstPtr sharData)
{
	sharData_ = std::move(sharData);
	itr_ = sharData_->selects.begin();
	voiceOneShot_ = false;
	Init();
}

void ResultUpdate::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	//ワンショットなので頻度が低い処理
	if (!voiceOneShot_) [[unlikely]]
	{
		voiceOneShot_ = true;
		//PlaySoundMem(sharData_->rank.soundHandle,DX_PLAYTYPE_BACK,false);
		lpVolumeMng.PlaySoundMem(sharData_->rank.soundHandle, Sound::Type::SE, DX_PLAYTYPE_BACK, false);
	}
	Select(input);
	auto& inputData = input.GetInputData();
	auto key = &inputData.at(keytype::Cast(keytype::RESULT::DECIDE));
	if (key->oneShot())
	{
		(*itr_)->func();
	}
}

void ResultUpdate::Init()
{
	for (auto& data : sharData_->selects)
	{
		data->blendParam = blendPrm;
	}
	(*itr_)->blendParam = NonblendPrm;
}

void ResultUpdate::Select(const InputManager& input)
{
	auto& inputData = input.GetInputData();
	auto& selects = sharData_->selects;
	auto key1 = &inputData.at(keytype::Cast(keytype::RESULT::LEFT));
	auto key2 = &inputData.at(keytype::Cast(keytype::RESULT::DOWN));
	auto flag = key1->oneShot() || key2->oneShot();
	if (flag && itr_ != --sharData_->selects.end())
	{
		(*itr_)->blendParam = blendPrm;
		++itr_;
		(*itr_)->blendParam = NonblendPrm;
	}
	key1 = &inputData.at(keytype::Cast(keytype::RESULT::RIGHT));
	key2 = &inputData.at(keytype::Cast(keytype::RESULT::UP));
	flag = key1->oneShot() || key2->oneShot();
	if (flag && itr_ != sharData_->selects.begin())
	{
		(*itr_)->blendParam = blendPrm;
		--itr_;
		(*itr_)->blendParam = NonblendPrm;
	}

}
