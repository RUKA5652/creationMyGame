#pragma once
#include<vector>
#include <string>
#include <mutex>
#define _PLAYSOUNDAPI_H_

namespace
{
	constexpr size_t DefBuffSize = 16;
	constexpr size_t DefHighDive = 16;
	constexpr float DefMag = 50.0;
}

class EqualizerEffect
{
public:
	struct RGB
	{
		int r = 255, g = 255, b = 255;
	};
	typedef struct Size
	{
		int x = 0, y = 0;
	}Pos;
	struct SetUpParam
	{
		using Path = std::string;
		using Handle = int;
		using Size = size_t;
		Path soundPath;
		Size buffSize = DefBuffSize;
		Size highDive = DefHighDive;
		//path���D�悳���
		Path imagePath;
		//path��handle�ǂ��炩���
		Handle imagehandle = -1;
		RGB color1;
		RGB color2;
	};


	EqualizerEffect();
	~EqualizerEffect();
	void LoadSound(const char* path);

	void ChengeSound(std::pair<std::string, int*>& data);

	bool PlaySound();

	void Draw();

	void SetUp(SetUpParam& param);

	Pos drawPos;
private:
	//�g�`�f�[�^�n���h��
	int softHandle_;
	//�T�E���h�n���h��
	int soundHandle_;

	size_t buffSize_;

	size_t highDive_;

	std::vector<float> paramList_;

	//�摜�n���h��
	int imageHandle_;
	//�摜�T�C�Y
	Size imageSize_;

	//blend�C���[�W
	int blendHandle_;

	//�{��
	float mag_;

	RGB color1_;
	RGB color2_;

	bool imageDeletFlag_;

	//shaderHandle
	int shaderHandle_;

	//changeSound���ꂽ���t���O
	bool changeFlag_;//�T�E���h�n���h���̍폜��������ł������Ȃ�

	std::mutex mtx_;

	void SetBuffSize(size_t buffSize);

	void SetGraph(const char* imagePath,int handle);

	void MakeBlendImage();


};

