#include "TitleHed.h"
#include "../../Select/Reel/Data/LoadReelData.h"
#include"../../Select/Reel/Data/SortReelData.h"
#include"TitleHedDraw.h"
#include"TitleHedUpdate.h"
#include"../../../../SoundWaveEffect/EqualizerEffect.h"
#include"../../Select/Reel/Sound/ReelSound.h"
#include <DxLib.h>

TitleHed::TitleHed(Beat::ReelDataPtr reelData, ReelSound*& reelSound)
	: ObjBase(1, 1)
{
	//リールデータ作成
	reelData_ = std::move(reelData);
	if (reelData_->sortData.size() == 0)
	{
		LoadReelData()(reelData_.get());
		SortReelData sort(reelData_);
		sort.CreateSortData();
		sort.Sort(Beat::ReelSortType::Name);
	}
	effect_ = new EqualizerEffect();

	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
	//更新セット
	draw_.emplace_back(std::make_shared<TitleHedDraw>(effect_));
	update_.emplace_back(std::make_unique<TitleHedUpdate>(reelData_, effect_, reelSound));
}

TitleHed::~TitleHed()
{
	delete effect_ ;
	//reelSound_はselectで引継ぎ使用するから開放しない
}
