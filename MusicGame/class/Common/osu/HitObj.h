#pragma once
#include<bitset>
#include<vector>
#include<memory>

namespace Beat
{
	using Line = int;
	using Time = int;
	using UpdateTime = int;
	//�m�[�c�ݒ�TYPE
	namespace Touch
	{
		using Type = int8_t;
		enum class TypeMode :unsigned int
		{
			HitCircle	= 0b1,
			Slider		= 0b10,
			NewCombo	= 0b100,
			Spinner		= 0b1000,
			SkipColler1 = 0b10000,
			SkipColler2 = 0b100000,
			SkipColler3 = 0b1000000,
			ManiaHold	= 0b10000000
		};

	};
	//���ݒ�TYPE
	namespace Sound
	{
		using Type = int8_t;

		enum class TypeMode
		{
			Normal = 0b0,
			Whistle = 0b10,
			Finish = 0b100,
			Clap = 0b1000
		};
	}
	/// <summary>
	/// osu�t�@�C������hitObj�f�[�^
	/// </summary>
	struct HitObj
	{
		HitObj()
		{
			line = 0;
			time = 0;
			type = 0;
			sound = 0;
			holdEndTime = 0;
		};
		//���[���ԍ�
		Line line;
		//�^�C�~���O
		Time time;
		//�m�[�c�^�C�v
		Touch::Type type;
		//�m�[�c���ݒ�
		Sound::Type sound;
		//�z�[���h�m�[�c�G���h�^�C�~���O
		Time holdEndTime;
	};
}


using HitObjVec = std::vector<Beat::HitObj>;

using HitObjVecConstPtr = std::shared_ptr<const HitObjVec>;

using HitObjVecPtr = std::shared_ptr<HitObjVec>;

