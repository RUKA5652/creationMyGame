#pragma once

namespace Beat
{
	/// <summary>
	/// �R���t�B�O�f�[�^
	/// �f�t�H���g�t�@�C���E���[�U�[�t�@�C�����Ȃ��������悤�Ƀf�[�^�����Ă���
	/// </summary>
	struct ConfigData
	{
		using mSpeed = int;
		using sidDivison = float;
		mSpeed ManiaSpeed = 15;
		sidDivison SideSpaceDivison = 0.25f;
	};
	
	using ConfigDataPtr = ConfigData*;
}

