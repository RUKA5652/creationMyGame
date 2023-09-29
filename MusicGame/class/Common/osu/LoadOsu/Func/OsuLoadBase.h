#pragma once
#include <string>
#include<fstream>
#include<memory>
#include "../../LoadData.h"
#include"LoadSectionBase.h"



/// <summary>
/// osu�t�@�C���ǂݍ��݃N���X
/// </summary>
class OsuLoadBase
{
public:
	const int version;
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="version">�o�[�W�������</param>
	/// <param name="loadData">���[�h�f�[�^�i�[��</param>
	OsuLoadBase(int&& version, Beat::LoadDataPtr& loadData);
	virtual ~OsuLoadBase();
	/// <summary>
	/// �t�@�C������ǂݍ���
	/// </summary>
	/// <param name="filePass">�ǂݍ��݃t�@�C���̃p�X</param>
	/// <returns></returns>
	virtual bool LoadOsuFile(const std::string& filePass);
protected:
	std::vector<Beat::LoadModule*> loadModule_;

	Beat::LoadDataPtr loadData_;


	void Init();


};
