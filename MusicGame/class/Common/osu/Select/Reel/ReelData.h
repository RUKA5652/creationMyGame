#pragma once
#include"../../../Base/BaseData.h"
#include"../../LoadData.h"
#include"Data/ReelSortType.h"
#include<map>
#include<list>
#include <filesystem>
#include<optional>

namespace Beat
{
	
	struct BeatMap
	{
		//フォルダパス
		std::string path;
		//ファイルネーム
		std::string filePath;
		//バックイメージ
		Beat::Events::BackImage image;
		//曲再生データ
		Beat::General general;
		//難易度、タイトル、作成者情報
		Beat::MetaData metaDatas;
		//難易度数値
		int Level;
	};


	struct ReelData
		:public BaseData
	{
		using FilePass = std::string;
		//全てのビートマップデータ
		using MapData = std::list<BeatMap>;
		//グループデータ
		using MapGroup = std::vector<const BeatMap*>;
		//全てのグループデータ
		using MainSortGroup = std::vector<MapGroup>;
		//全てのビートマップデータ
		MapData beatMapData;
		//全てのグループデータ
		MainSortGroup sortData;
		//選ばれているグループ
		std::optional<int> mainSortIndex_;
		//選ばれている曲
		std::optional<int>  mapGroupIndex_;

		std::optional<ReelSortType> sortType;

		const MapGroup* GetMapGroupData() const;
		const BeatMap* GetMapData() const;

		bool MoveMainSort(int cnt);

		bool MoveBeatMap(int cnt);

		void reset()
		{
			beatMapData.clear();
			sortData.clear();
		}
	};

	using ReelDataPtr = std::shared_ptr<ReelData>;
	using ReelDataConstPtr = std::shared_ptr<const ReelData>;
}

