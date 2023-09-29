#pragma once
#include<string>
#include"HitObj.h"

namespace Beat
{
	//プレイモード
	enum class GameMode :int
	{
		Non = -1,
		Osu = 0,
		Taiko = 1,
		Catch = 2,
		Mania = 3,
	};
	//サウンドセット
	enum class SampleSet :int
	{
		NON,
		Normal,
		Soft,
		Drum,
	};
	/// <summary>
	/// osuファイル　General情報
	/// </summary>
	struct General
	{
		//再生ファイル
		std::string AudioFilename;
		//再生までの空白ms
		Time AudioLeadIn = 0;
		//曲の再生位置ms
		Time PreviewTime = 0;
		//モード
		GameMode Mode = GameMode::Non;
		//サンプルセット　デフォルトで使われる音のセット
		SampleSet SampleSet = SampleSet::Normal;
		void clear()
		{
			AudioFilename = "";
			AudioLeadIn = 0;
			PreviewTime = 0;
			Mode = GameMode::Non;
			SampleSet = SampleSet::Normal;
		}

	};
	using GeneralPtr = General*;
	using GeneralConstPtr = const General*;
}

