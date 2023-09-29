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
/// osu�t�@�C���̏��i�[
/// �|�C���^�[��������̂�����ǂݍ���
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
		//�S�Ă𐶐�����
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
		//�����������̂�j��
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
		//�t�H���_�p�X
		std::string folderPath;
		//�m�[�c���
		HitObjVecPtr hitObjVec;
		//Difficulty���
		DifficultyPtr difficulty;
		//�W�F�l�����f�[�^
		General* generalData;
		//�C�x���g�f�[�^
		Events* eventsData;
		//MetaData
		MetaData* metaData;
		//�^�C�~���O�|�C���g
		TimingPointsPtr timingPoints;
		//�X�R�A�{��
		ScoreMagDataPtr scoreMagData;
	};
	using LoadDataCPtr = std::shared_ptr<const Beat::LoadData>;
	using LoadDataPtr = std::shared_ptr<Beat::LoadData>;
}


