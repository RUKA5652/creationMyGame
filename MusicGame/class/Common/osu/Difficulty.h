#pragma once

namespace Beat
{
	/// <summary>
	/// osu�t�@�C������Difficulty�f�[�^
	/// </summary>
	struct Difficulty
	{
		//HP�����l
		int HPDrainRate;
		//mania::�L�[��
		int CircleSize;
		//���ʂ̓�Փx�S�̂����肷��v�f
		int OverallDifficulty;
		//�t�F�[�h �C�����n�߂�^�C�~���O�FOSU/catch�p
		int ApproachRate;
		//�X���C�_�[�̒����⑬�x
		double SliderMultiplier;
		//�������\���p�x
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
