#pragma once
#include<map>
#include<vector>

namespace Beat
{
	/// <summary>
	/// �K�p����C���[�W�f�[�^
	/// </summary>
	enum class SkinImageType
	{
		//�Q�[�����
		//�m�[�c
		Notes1,
		Notes2,
		Notes5,
		//�z�[���h��
		HoldLane1,
		HoldLane2,
		HoldLane5,
		//�m�[�c���C�g
		NotesLighth,
		//�z�[���h�m�[�c���C�g
		HoldLighth,
		//���[��
		Lane,
		//���[�����C�g
		LaneLighth,
		//����o�[
		DecisionBar,
		//�R���{�`��
		JUST,
		Great,
		Good,
		Bad,
		//�Z���N�g���
		//�y�ȃt�H���_
		MusicFolder,
		//��Փx
		Level,
		//����
		num,
		scoreX,
		//���U���g
		Rank,
		//����
		RankSSH,
		RankSS,
		RankSH,
		RankS,
		RankA,
		RankB,
		RankC,
		RankD,
		//�Ⴂ
		Score,
		//���g���C
		Retry,
		//Back
		BACK,
	};
	
	using SkinImage = int;

	using SkinImageMap = std::map<SkinImageType, std::vector<SkinImage>>;


}
