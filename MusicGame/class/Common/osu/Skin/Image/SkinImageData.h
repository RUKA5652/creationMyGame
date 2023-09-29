#pragma once
#include<map>
#include<vector>

namespace Beat
{
	/// <summary>
	/// 適用するイメージデータ
	/// </summary>
	enum class SkinImageType
	{
		//ゲーム画面
		//ノーツ
		Notes1,
		Notes2,
		Notes5,
		//ホールド間
		HoldLane1,
		HoldLane2,
		HoldLane5,
		//ノーツライト
		NotesLighth,
		//ホールドノーツライト
		HoldLighth,
		//レーン
		Lane,
		//レーンライト
		LaneLighth,
		//判定バー
		DecisionBar,
		//コンボ描画
		JUST,
		Great,
		Good,
		Bad,
		//セレクト画面
		//楽曲フォルダ
		MusicFolder,
		//難易度
		Level,
		//数字
		num,
		scoreX,
		//リザルト
		Rank,
		//高い
		RankSSH,
		RankSS,
		RankSH,
		RankS,
		RankA,
		RankB,
		RankC,
		RankD,
		//低い
		Score,
		//リトライ
		Retry,
		//Back
		BACK,
	};
	
	using SkinImage = int;

	using SkinImageMap = std::map<SkinImageType, std::vector<SkinImage>>;


}
