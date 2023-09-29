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
		//pathが優先される
		Path imagePath;
		//pathとhandleどちらか一つ
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
	//波形データハンドル
	int softHandle_;
	//サウンドハンドル
	int soundHandle_;

	size_t buffSize_;

	size_t highDive_;

	std::vector<float> paramList_;

	//画像ハンドル
	int imageHandle_;
	//画像サイズ
	Size imageSize_;

	//blendイメージ
	int blendHandle_;

	//倍率
	float mag_;

	RGB color1_;
	RGB color2_;

	bool imageDeletFlag_;

	//shaderHandle
	int shaderHandle_;

	//changeSoundされたかフラグ
	bool changeFlag_;//サウンドハンドルの削除をこちらでしたくない

	std::mutex mtx_;

	void SetBuffSize(size_t buffSize);

	void SetGraph(const char* imagePath,int handle);

	void MakeBlendImage();


};

