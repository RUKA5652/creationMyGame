#pragma once
#include"../Base/BaseData.h"
#include"HitObj.h"
#include"Difficulty.h"
#include"GeneralData.h"
#include"EventsData.h"
#include"MetaData.h"
#include"TimingPointsData.h"
#include"ScoreMagData.h"
#include<memory>

/// <summary>
/// osuファイルの情報格納
/// ポインターがあるものだけを読み込む
/// </summary>
namespace Beat
{
	struct LoadData
		:public BaseData
	{
		LoadData()
		{
 			hitObjVec = nullptr;
			difficulty = nullptr;
			generalData = nullptr;
			eventsData = nullptr;
			metaData = nullptr;
		}
		//全てを生成する
		void AllInstance()
		{
			hitObjVec = std::make_shared<HitObjVec>();
			difficulty = new Difficulty();
			generalData = new General();
			eventsData = new Events();
			metaData = new MetaData();
			timingPoints = std::make_shared<TimingPoints>();
			scoreMagData = std::make_shared<ScoreMagData>();
		}
		//生成したものを破棄
		~LoadData()
		{
			hitObjVec.reset();
			delete difficulty;
			delete generalData;
			delete eventsData;
			delete metaData;
			timingPoints.reset();
			scoreMagData.reset();
		}
		//フォルダパス
		std::string folderPath;
		//ノーツ情報
		HitObjVecPtr hitObjVec;
		//Difficulty情報
		DifficultyPtr difficulty;
		//ジェネラルデータ
		General* generalData;
		//イベントデータ
		Events* eventsData;
		//MetaData
		MetaData* metaData;
		//タイミングポイント
		TimingPointsPtr timingPoints;
		//スコア倍率
		ScoreMagDataPtr scoreMagData;
	};
	using LoadDataCPtr = std::shared_ptr<const Beat::LoadData>;
	using LoadDataPtr = std::shared_ptr<Beat::LoadData>;
}


