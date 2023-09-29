#pragma once
#include"HitObj.h"
#include<bitset>
#include"GeneralData.h"

/// <summary>
/// データ定義
/// OSUデータ　TimingPoint
/// </summary>
namespace Beat
{
	struct TimingPoint
	{
		using Effect = std::bitset<2>;

		enum class EffectType
		{
			Non,
			Kiai,
			Ellipsis
		};

		//タイミングセクション開始
		Time time;
		//拍の継続時間,継承フラグが立っていたら負の逆のスライダー速度乗数(パーセント)
		double beatLength;
		//小節の拍数
		int meter;
		//ヒットオブジェクトの音量（パーセント）
		int volume;
		//継承フラグ
		int uninertied;
		//サビ、気合タイム
		Effect effects;
		//音タイプ
		SampleSet sampleSet;
		//通常使用するsampleセット
		int sampleIndex;
	};
}
using TimingPoints = std::vector<Beat::TimingPoint>;
using TimingPointsPtr = std::shared_ptr<TimingPoints>;