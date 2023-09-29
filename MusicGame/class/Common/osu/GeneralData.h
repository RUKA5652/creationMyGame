#pragma once
#include<string>
#include"HitObj.h"

namespace Beat
{
	//�v���C���[�h
	enum class GameMode :int
	{
		Non = -1,
		Osu = 0,
		Taiko = 1,
		Catch = 2,
		Mania = 3,
	};
	//�T�E���h�Z�b�g
	enum class SampleSet :int
	{
		NON,
		Normal,
		Soft,
		Drum,
	};
	/// <summary>
	/// osu�t�@�C���@General���
	/// </summary>
	struct General
	{
		//�Đ��t�@�C��
		std::string AudioFilename;
		//�Đ��܂ł̋�ms
		Time AudioLeadIn = 0;
		//�Ȃ̍Đ��ʒums
		Time PreviewTime = 0;
		//���[�h
		GameMode Mode = GameMode::Non;
		//�T���v���Z�b�g�@�f�t�H���g�Ŏg���鉹�̃Z�b�g
		SampleSet SampleSet = SampleSet::Normal;
		void clear()
		{
			AudioFilename = "";
			AudioLeadIn = 0;
			PreviewTime = 0;
			Mode = GameMode::Non;
			SampleSet = SampleSet::Normal;
		}

	};
	using GeneralPtr = General*;
	using GeneralConstPtr = const General*;
}

