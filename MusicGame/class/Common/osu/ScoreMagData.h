#pragma once
#include<map>
#include"game/DecisionData.h"

/// <summary>
/// �f�[�^��`
/// �X�R�A
/// </summary>
namespace Beat
{
	//�錾 �C���N���[�h���Ă��G���[���o�Ă��܂�
	inline namespace HitResult
	{
		enum class Type;
	}
	//�ő僌�x��
	constexpr int maxLevel = 15;
	//�X�R�A�f�[�^
	struct ScoreMagData
	{
		//�_���z��
		std::map <Beat::HitResult::Type, double > scoreMagData;
		//�z�[���h�p������܂ł̎���
		Beat::Time midpoint = 0;
		//�ő�R���{��
		int maxCombo = 0; 
		//���ʃ��x��
		int level = 0;
	};
}
using ScoreMagDataPtr = std::shared_ptr<Beat::ScoreMagData>;


