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
		//�t�H���_�p�X
		std::string path;
		//�t�@�C���l�[��
		std::string filePath;
		//�o�b�N�C���[�W
		Beat::Events::BackImage image;
		//�ȍĐ��f�[�^
		Beat::General general;
		//��Փx�A�^�C�g���A�쐬�ҏ��
		Beat::MetaData metaDatas;
		//��Փx���l
		int Level;
	};


	struct ReelData
		:public BaseData
	{
		using FilePass = std::string;
		//�S�Ẵr�[�g�}�b�v�f�[�^
		using MapData = std::list<BeatMap>;
		//�O���[�v�f�[�^
		using MapGroup = std::vector<const BeatMap*>;
		//�S�ẴO���[�v�f�[�^
		using MainSortGroup = std::vector<MapGroup>;
		//�S�Ẵr�[�g�}�b�v�f�[�^
		MapData beatMapData;
		//�S�ẴO���[�v�f�[�^
		MainSortGroup sortData;
		//�I�΂�Ă���O���[�v
		std::optional<int> mainSortIndex_;
		//�I�΂�Ă����
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

