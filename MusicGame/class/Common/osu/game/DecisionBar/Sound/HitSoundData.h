#pragma once
#include<vector>
#include <map>
#include "../../../Skin/Sound/SkinSoundData.h"
#include"../../../HitObj.h"
#include"../../../GeneralData.h"

namespace Decision
{
	enum class CustomSet
	{
		Def,
		BeatMap,
	};

	using HitSoundData = std::map<Beat::Sound::Type,Beat::SoundData>;
	using HitSoundSetData = std::map<Beat::SampleSet, HitSoundData>;
	using HitSoundCustomSet = std::map<CustomSet, HitSoundSetData>;
	//�f�t�H���g�̃T�E���h
	//�ȌŗL�̃T�E���h �ȃt�H���_�ɊY�����鉹������Γǂݍ���Ŏg�p����
	//�^�C�~���O�|�C���g��sampleIndex��0�̎��f�t�H���g�T�E���h�ōĐ�
	//�P�����̓C���f�b�N�X-1���ꂽ�t�@�C�����Đ�

}
