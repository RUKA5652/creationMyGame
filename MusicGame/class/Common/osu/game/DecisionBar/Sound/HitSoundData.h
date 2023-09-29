#pragma once
#include<vector>
#include <map>
#include "../../../Skin/Sound/SkinSoundData.h"
#include"../../../HitObj.h"
#include"../../../GeneralData.h"

namespace Decision
{
	enum class CustomSet
	{
		Def,
		BeatMap,
	};

	using HitSoundData = std::map<Beat::Sound::Type,Beat::SoundData>;
	using HitSoundSetData = std::map<Beat::SampleSet, HitSoundData>;
	using HitSoundCustomSet = std::map<CustomSet, HitSoundSetData>;
	//デフォルトのサウンド
	//曲固有のサウンド 曲フォルダに該当する音があれば読み込んで使用する
	//タイミングポイントのsampleIndexが0の時デフォルトサウンドで再生
	//１から上はインデックス-1されたファイルを再生

}
