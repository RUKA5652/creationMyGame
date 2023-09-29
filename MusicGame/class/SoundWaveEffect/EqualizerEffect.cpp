#include "EqualizerEffect.h"
#define NOMINMAX
#include<DxLib.h>
#include<algorithm>
#include<thread>
#include"../shaderDraw/DxShDraw.h"
#include "../SoundVolume/SoundVolume.h"

EqualizerEffect::EqualizerEffect()
{
	softHandle_ = -1;
	soundHandle_ = -1;
	highDive_ = DefHighDive;
	mag_ = DefMag;
	SetBuffSize(DefBuffSize);
	changeFlag_ = false;

	shaderHandle_ = LoadPixelShader("resource/shader/AdditiveColor.pso");
}

EqualizerEffect::~EqualizerEffect()
{
	while (!mtx_.try_lock())
	{

	}

	DeleteSoftSound(softHandle_);
	if (!changeFlag_)
	{
		DeleteSoundMem(soundHandle_);
	}
	if (imageDeletFlag_)
	{
		DeleteGraph(imageHandle_);
	}
	DeleteGraph(blendHandle_);
	DeleteShader(shaderHandle_);
	mtx_.unlock();
}

void EqualizerEffect::LoadSound(const char* path)
{
	std::lock_guard<std::mutex> lock(mtx_);
	if (path == nullptr)
	{
		return;
	}
	DeleteSoftSound(softHandle_);
	softHandle_ = -1;
	if (!changeFlag_)
	{
		StopSoundMem(soundHandle_);
		DeleteSoundMem(soundHandle_);
	}	
	soundHandle_ = -1;
	changeFlag_ = false;
	softHandle_ = LoadSoftSound(path);
	soundHandle_ = LoadSoundMemFromSoftSound(softHandle_);
}

void EqualizerEffect::ChengeSound(std::pair<std::string, int*>& data)
{
	std::lock_guard<std::mutex> lock(mtx_);
	DeleteSoftSound(softHandle_);
	softHandle_ = -1;
	if (!changeFlag_)
	{
		StopSoundMem(soundHandle_);
		DeleteSoundMem(soundHandle_);
	}
	soundHandle_ = -1;
	changeFlag_ = true;
	softHandle_ = LoadSoftSound(data.first.c_str());
	std::thread thread([=]() {while (*data.second <= 0 ){};
	soundHandle_ = *data.second; });
	thread.detach();
}

bool EqualizerEffect::PlaySound()
{
	return lpVolumeMng.PlaySoundMem(soundHandle_, Sound::Type::Song, DX_PLAYTYPE_LOOP);
}

void EqualizerEffect::Draw()
{
	auto inScreen = GetDrawScreen();
	MakeBlendImage();
	SetDrawScreen(inScreen);


	DxShDraw::DrawGraph(drawPos.x, drawPos.y, imageHandle_, blendHandle_, shaderHandle_);
}

void EqualizerEffect::SetUp(SetUpParam& param)
{
	LoadSound(param.soundPath.c_str());
	SetBuffSize(param.buffSize);
	SetGraph(param.imagePath.c_str(),param.imagehandle);
	highDive_ = param.highDive;
	color1_ = param.color1;
	color2_ = param.color2;
}

void EqualizerEffect::SetBuffSize(size_t buffSize)
{
	buffSize_ = buffSize;
	paramList_.resize(buffSize);
}

void EqualizerEffect::SetGraph(const char* imagePath, int handle)
{
	if (imagePath == nullptr)
	{
		imageDeletFlag_ = false;
		imageHandle_ = handle;
	}
	else
	{
		imageDeletFlag_ = true;
		imageHandle_ = LoadGraph(imagePath);
	}
	
	int x, y;
	GetGraphSize(imageHandle_,&x,&y);
	imageSize_ = {x,y};
	blendHandle_ = MakeScreen(imageSize_.x,imageSize_.y,true);
}

void EqualizerEffect::MakeBlendImage()
{
	if (!mtx_.try_lock())
	{
		SetDrawScreen(blendHandle_);
		ClearDrawScreen();
		return;
	}
	SetDrawScreen(blendHandle_);
	ClearDrawScreen();

	auto nowPos = GetCurrentPositionSoundMem(soundHandle_);
	auto size = paramList_.size();
//	DrawBox(0, 0, imageSize_.x, imageSize_.y, 0xff0000, true);
	float sizeY = imageSize_.y / static_cast<float>(highDive_);
	float sizeX = imageSize_.x / static_cast<float>(size);

	GetFFTVibrationSoftSound(softHandle_, -1, nowPos, 1024, paramList_.data(), static_cast<int>(paramList_.size()));
	for (int i = 0; i < size; i++)
	{
		paramList_[i] = std::pow(paramList_[i], 0.5f) * mag_;
		paramList_[i] = std::min(paramList_[i], static_cast<float>(highDive_));
		DrawBox(i * static_cast<int>(sizeX), imageSize_.y - (int)(paramList_[i] * sizeY),
			static_cast<int>((static_cast<float>(i) + 1) * sizeX), imageSize_.y, GetColor(color1_.r, color1_.g, color1_.b), TRUE);
		DrawBox(imageSize_.x - i * static_cast<int>(sizeX) , 0,
			imageSize_.x - static_cast<int>((static_cast<float>(i) + 1) * sizeX), static_cast<int>(paramList_[i] * sizeY),
			GetColor(color2_.r, color2_.g, color2_.b), TRUE);
	}
	mtx_.unlock();
}

