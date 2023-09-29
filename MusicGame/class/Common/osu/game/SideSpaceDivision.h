#pragma once
#include"../../Base/BaseData.h"
#include<memory>
#include"../Difficulty.h"

/// <summary>
/// ��ʗ��[�̋󂫃X�y�[�X�̃T�C�Y��������
/// </summary>
class SideSpaceDivision
	:public BaseData
{
public:
	SideSpaceDivision();

	/// <summary>
	/// �擾
	/// ��ʒ[���ǂꂾ���c���̂��̕�����
	/// </summary>
	const double& GetDivisionSpaceRatio() const;
	void SetDivison(double data);
private:


	//��ʒ[���ǂꂾ���c���̂��̕�����
	double divisionSpaceRatio;

};
