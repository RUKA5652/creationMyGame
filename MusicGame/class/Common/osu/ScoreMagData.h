#pragma once
#include<map>
#include"game/DecisionData.h"

/// <summary>
/// データ定義
/// スコア
/// </summary>
namespace Beat
{
	//宣言 インクルードしてもエラーが出てしまう
	inline namespace HitResult
	{
		enum class Type;
	}
	//最大レベル
	constexpr int maxLevel = 15;
	//スコアデータ
	struct ScoreMagData
	{
		//点数配分
		std::map <Beat::HitResult::Type, double > scoreMagData;
		//ホールド継続判定までの時間
		Beat::Time midpoint = 0;
		//最大コンボ数
		int maxCombo = 0; 
		//譜面レベル
		int level = 0;
	};
}
using ScoreMagDataPtr = std::shared_ptr<Beat::ScoreMagData>;


