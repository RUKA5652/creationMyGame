#pragma once

namespace Beat
{
	/// <summary>
	/// osuファイル内のDifficultyデータ
	/// </summary>
	struct Difficulty
	{
		//HP減衰値
		int HPDrainRate;
		//mania::キー数
		int CircleSize;
		//譜面の難易度全体を決定する要素
		int OverallDifficulty;
		//フェード インし始めるタイミング：OSU/catch用
		int ApproachRate;
		//スライダーの長さや速度
		double SliderMultiplier;
		//メモリ表示頻度
		int SliderTickRate;

		void clear()
		{
			HPDrainRate = -1;
			CircleSize = -1;
			OverallDifficulty = -1;
			ApproachRate = -1;
			SliderMultiplier = -1;
			SliderTickRate = -1;
		}

	};
	using DifficultyPtr = Difficulty*;
	using DifficultyConstPtr = const Difficulty*;
}
