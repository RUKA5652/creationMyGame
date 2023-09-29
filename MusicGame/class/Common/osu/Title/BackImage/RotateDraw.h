#pragma once
#include <array>
#include<DxLib.h>
#include<vector>
#include<random>
#include<thread>
#include<filesystem>
#include "../../../../Timer/Timer.h"
#include"../../../template/Vector2.h"


/// <summary>
/// ���^�C�g���w�i�I�u�W�F�N�g�̕`�� 
/// </summary>
class RotateDraw
{
public:
	RotateDraw();
	~RotateDraw();
	//�`��
	void Draw();
	//�X�V
	void Update(Timer::DeletaTimeConst& delta);
private:
	struct PolyData
	{
		//��]�̒��S
		FLOAT3 center;
		//�ړ��x�N�g��
		FLOAT2  moveVec;
		//�p�x
		float deg;
		//�C���[�W�n���h��
		int image;
		//�`��|���S���f�[�^
		std::array<VERTEX3D, 4> poly;
	};
	//���\�[�X�t�H���_�f�[�^
	std::vector<int> imageHandles_;

	//���������p�X���b�h
	std::jthread geneThread_;

	//���ݐ������ꂢ�Ă鐔
	int geneCnt_;

	//�|���S���f�[�^�Q
	std::vector<PolyData> polyDatas_;

	//����������
	std::mt19937_64 rand_;

	//�����ő吔
	int maxCnt_;

	//�����ҋ@����
	int waitTime_;

	//�傫���̍ŏ��l
	float sizeBtom_;

	//�F�̍ŏ��l
	float colorBtom_;

	//��]�p�̏��
	int degree_;

	//�ړ�����
	Vector2 moveVec_;

	//�|���S���f�[�^�쐬
	void MakePolyData();
	//PolyData�̒l�����Z�b�g����
	void MakePoly(PolyData& polyData, FLOAT2 pos, FLOAT4 color, float sizeX, float sizeY);
	//Y����]
	void Rotate(PolyData& polyData, Timer::DeletaTimeConst& delta);
	//�ړ�
	void Move(PolyData& polyData , Timer::DeletaTimeConst& delta);
	//�폜�`�F�b�N
	void CheckDelet();
	//����
	void MakeGenerationThread();
	// <param name="num">�l�͈�</param>
	float GetRand(float num);
	//�t�H���_���[�h�ɓ�����֐�
	void SetImage(const std::filesystem::path& path, std::string&& fileName);
	//�ݒ�ǂݍ���
	std::string Load();
};

