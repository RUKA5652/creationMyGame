#include "SoundVolume.h"
#include"Input/Create.h"
#include "../Input/EnumCast.h"
#include"Input/Enum.h"
#include <algorithm>
#include"../shaderDraw/DxShDraw.h"
#include"../Common/WindowSize.h"
#include"../AnimCurve/animCurve.h"
#include<fstream>
#include <filesystem>

namespace
{
	constexpr SoundVolume::volume MaxVolume = 255;
	constexpr SoundVolume::volume MinVolume = 0;
	constexpr Vector2 offset(50,50);
	constexpr Timer::DeletaTime MaxTime = 1000;
	constexpr const char* filePath = "resource/volume.vol";
}

SoundVolume::SoundVolume()
{
	CreateVoulumeInput()(input_);
	using enum Sound::Type;
	for (int i = 0; i < static_cast<int>(MAX); i++)
	{
		soundHandle_.try_emplace(static_cast<Sound::Type>(i));
	}
	LoadVolume();
	auto size = lpWindowSize->GetSize();
	screen_ = MakeScreen(size.x, size.y,true);

	shaderHndle_ = LoadPixelShader("resource/shader/CoreThickness.pso");

	songDrawPrm_.mainTex = LoadGraph("resource/skin/UI/Sound/mainTex.png");
	songDrawPrm_.thickTex = LoadGraph("resource/skin/UI/Sound/mask.png");
	songDrawPrm_.buffHandle_ = CreateShaderConstantBuffer(sizeof(float)*4);
	songDrawPrm_.backImage = LoadGraph("resource/skin/UI/Sound/UnderTexSong.png");

	seDrawPrm_.mainTex = songDrawPrm_.mainTex;
	seDrawPrm_.thickTex = songDrawPrm_.thickTex;
	seDrawPrm_.buffHandle_ = songDrawPrm_.buffHandle_;
	seDrawPrm_.backImage = LoadGraph("resource/skin/UI/Sound/UnderTexSe.png");

	update_ = {
		{State::NON,std::bind_front(&SoundVolume::UpdateNon,this)},
		{State::STANDBY,std::bind_front(&SoundVolume::UpdateStandby,this)},
		{State::OPUNE,std::bind_front(&SoundVolume::UpdateVolume,this)}
	};

	nowState_ = State::NON;

	clauseTime_ = 0;
}

SoundVolume::~SoundVolume()
{
	DeleteShader(shaderHndle_);
	Save();
}

void SoundVolume::Save()
{
	auto stream = std::ofstream(filePath, std::ios::binary);
	for (auto& data : volume_)
	{
		stream.write(reinterpret_cast<char*>(&data), sizeof(data));
	}
}

void SoundVolume::LoadVolume()
{
	using enum Sound::Type;
	for (int i = 0; i < static_cast<int>(MAX); i++)
	{
		volume_.try_emplace(static_cast<Sound::Type>(i),MaxVolume);
	}
	if (std::filesystem::exists(filePath))
	{
		std::ifstream stream(filePath, std::ios::binary);
		std::pair<Sound::Type, volume> data;
		while (stream)
		{
			auto size = sizeof(data);
			stream.read(reinterpret_cast<char*>(&data), sizeof(data));
			volume_.insert_or_assign(data.first, data.second);
		}
	}
}

int SoundVolume::GetVolume(Sound::Type type) const
{
	return static_cast<int>(volume_.at(type));
}

int SoundVolume::PlaySoundMem(int handle, Sound::Type type, int PlayType, int TopPositionFlag) const
{
	ChangeNextPlayVolumeSoundMem(GetVolume(type),handle);
	return DxLib::PlaySoundMem(handle, PlayType,TopPositionFlag);
}

void SoundVolume::SetFollowingHandle(int handle, Sound::Type type)
{
	soundHandle_.at(type).push_back(handle);
}

void SoundVolume::RemoveSetFollowingHandle(int handle, Sound::Type type)
{
	std::ranges::remove_if(soundHandle_.at(type), [handle](auto& data) {return data == handle; });
}

void SoundVolume::ProcessInput()
{
	timer_.UpdateDelta();
	input_->Update(timer_.GetDeletaTime());
	CountClause();
	update_.at(nowState_)();
}

void SoundVolume::DrawParam(Vector2 pos)
{
	if (nowState_ == State::NON)
	{
		return;
	}
	songDrawPrm_.thickness = volume_.at(Sound::Type::Song) / MaxVolume;
	seDrawPrm_.thickness = volume_.at(Sound::Type::SE) / MaxVolume;

	auto& size = lpWindowSize->GetSize();
	Vector2 grapSize;
	GetGraphSize(songDrawPrm_.thickTex,&grapSize.x, &grapSize.y);
	ShaderDraw(Vector2{ size.x,  size.y} - grapSize * 2 + offset - pos, songDrawPrm_);
	ShaderDraw(Vector2{ size.x,  size.y} - grapSize - pos, seDrawPrm_);
}

void SoundVolume::ShaderDraw(Vector2 pos,shaderPrm& prm)
{
	
	auto inScreen = GetDrawScreen();
	auto t = static_cast<float>(clauseTime_)/ MaxTime;
	t = 255.0f * (1.0f - ReBaseCurve(t, 8));
	auto ti = static_cast<int>(t);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ti);
	DrawGraph(pos.x, pos.y, prm.backImage, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, ti);
	SetDrawScreen(screen_);
	ClearDrawScreen();
	DxShDraw::DrawGraph(pos.x, pos.y, prm.mainTex, [&]() {
		SetUsePixelShader(shaderHndle_);
	SetUseTextureToShader(0, prm.mainTex);
	SetUseTextureToShader(1, prm.thickTex);
	auto buff = static_cast<float*>(GetBufferShaderConstantBuffer(prm.buffHandle_));
	buff[0] = prm.thickness;
	UpdateShaderConstantBuffer(prm.buffHandle_);
	SetShaderConstantBuffer(prm.buffHandle_, DX_SHADERTYPE_PIXEL, 0);
		});
	SetDrawScreen(inScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ti);
	DrawGraph(0, 0, screen_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, ti);
}

void SoundVolume::UpdateVolume()
{
	using enum VolumeInput;
	using enum Sound::Type;
	auto& data = input_->GetInputData();
	auto* key = &data.at(Cast(SeUp));
	auto* vol = &volume_.at(SE);
	auto* follHandle = &soundHandle_.at(SE);
	auto time = timer_.GetDeletaTime();
	auto update = [&](int sign) {
		if (key->now)
		{
			*vol += sign * time * 1.0f/6;
			*vol = std::clamp(*vol, MinVolume, MaxVolume);
			for (const auto& handle : *follHandle)
			{
				ChangeVolumeSoundMem(static_cast<int>(*vol) ,handle);
			}
		}
	};

	vol = &volume_.at(SE);
	follHandle = &soundHandle_.at(SE);
	key = &data.at(Cast(SeUp));
	update(1);
	key = &data.at(Cast(SeDown));
	update(-1);

	vol = &volume_.at(Song);
	follHandle = &soundHandle_.at(Song);
	key = &data.at(Cast(SongUp));
	update(1);
	key = &data.at(Cast(SongDown));
	update(-1);


}

void SoundVolume::UpdateNon()
{
	auto& data = input_->GetInputData();
	for (auto& key : data)
	{
		if (key.second.oneShot())
		{
			nowState_ = State::STANDBY;
			return;
		}
	}
}

void SoundVolume::UpdateStandby()
{
	auto& data = input_->GetInputData();
	for (auto& key : data)
	{
		if (key.second.oneShot())
		{
			nowState_ = State::OPUNE;
		}
		if (key.second.now)
		{
			return;
		}
	}
}

void SoundVolume::CountClause()
{
	if (nowState_ == State::NON)
	{
		clauseTime_ = 0;
	}
	else
	{
		clauseTime_ += timer_.GetDeletaTime();
		if (clauseTime_ >= MaxTime)
		{
			nowState_ = State::NON;
			clauseTime_ = 0;
		}	
		auto& data = input_->GetInputData();
		for (auto& key : data)
		{
			if (key.second.now)
			{
				clauseTime_ = 0;
				return;
			}
		}

	}
}

SoundVolume::shaderPrm::~shaderPrm()
{
	DeleteGraph(mainTex); 
	DeleteGraph(thickTex);
	DeleteShaderConstantBuffer(buffHandle_);
	DeleteGraph(backImage);
}
