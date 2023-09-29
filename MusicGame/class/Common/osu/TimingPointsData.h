#pragma once
#include"HitObj.h"
#include<bitset>
#include"GeneralData.h"

/// <summary>
/// �f�[�^��`
/// OSU�f�[�^�@TimingPoint
/// </summary>
namespace Beat
{
	struct TimingPoint
	{
		using Effect = std::bitset<2>;

		enum class EffectType
		{
			Non,
			Kiai,
			Ellipsis
		};

		//�^�C�~���O�Z�N�V�����J�n
		Time time;
		//���̌p������,�p���t���O�������Ă����畉�̋t�̃X���C�_�[���x�搔(�p�[�Z���g)
		double beatLength;
		//���߂̔���
		int meter;
		//�q�b�g�I�u�W�F�N�g�̉��ʁi�p�[�Z���g�j
		int volume;
		//�p���t���O
		int uninertied;
		//�T�r�A�C���^�C��
		Effect effects;
		//���^�C�v
		SampleSet sampleSet;
		//�ʏ�g�p����sample�Z�b�g
		int sampleIndex;
	};
}
using TimingPoints = std::vector<Beat::TimingPoint>;
using TimingPointsPtr = std::shared_ptr<TimingPoints>;