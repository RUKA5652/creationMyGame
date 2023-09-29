#include "ComboUpdate.h"
#include"../../../osu/Skin/FolderSearch.h"
#include<algorithm>
#include "../../../../SoundVolume/SoundVolume.h"

ComboUpdate::ComboUpdate(Beat::HitsDataConstPtr hitdata)
{
	hitdata_ = hitdata;
	oldHitCount_ = 0;
	CreateSound();

}

ComboUpdate::~ComboUpdate()
{
	for (auto [key, handle] : soundHandle_)
	{
		DeleteSoundMem(handle);
	}
}

void ComboUpdate::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	if (hitdata_->combo != oldHitCount_)
	{
		bool playFlag = false;
		if (hitdata_->combo == 0)
		{
			itr_ = soundHandle_.begin();
			if (oldHitCount_ >= 50)
			{
				playFlag = true;
			}
			else if (itr_->first == 0)
			{
				++itr_;
			}
		}
		printf("%d\n", hitdata_->combo - itr_->first);
		if (hitdata_->combo - itr_->first >= 0 && oldHitCount_ < itr_->first)
		{
			playFlag = true;
		}
		if (playFlag)
		{
			//PlaySoundMem(itr_->second, DX_PLAYTYPE_BACK,false);
			lpVolumeMng.PlaySoundMem(itr_->second, Sound::Type::SE, DX_PLAYTYPE_BACK,false);
			++itr_;
			if (soundHandle_.end() == itr_)
			{
				--itr_;
			}
		}
	}
	oldHitCount_ = hitdata_->combo;
}

void ComboUpdate::CreateSound()
{
	FolderSearch(std::bind_front(&ComboUpdate::SetSound, this))("resource/skin/Combo");
	std::ranges::sort(soundHandle_, [](auto nam1, auto nam2) {return nam1.first < nam2.first; });
	itr_ = soundHandle_.begin();
	if (itr_->first == 0)
	{
		++itr_;
	}
}

void ComboUpdate::SetSound(const std::filesystem::path& path, std::string&& name)
{
	soundHandle_.emplace_back(std::stoi(name), LoadSoundMem(path.string().c_str()));
}
